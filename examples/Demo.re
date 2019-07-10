[%raw "require('isomorphic-fetch')"];

module Error = ReludeFetch.Error;
module Headers = ReludeFetch.Headers;

module ResultE =
  Relude.Result.WithError({
    type t = string;
  });

module IOE =
  Relude.IO.WithError({
    type t = Error.t(string);
  });

let (>>=) = IOE.Infix.(>>=);

module Data = {
  type t = {
    foo1: string,
    foo2: string,
  };

  let show = data => "{foo1:" ++ data.foo1 ++ ", foo2:" ++ data.foo2 ++ "}";

  let decode: Js.Json.t => Belt.Result.t(t, string) =
    json => {
      json
      |> Js.Json.decodeObject
      |> Relude.Option.flatMap(dict => Js.Dict.get(dict, "args"))
      |> Relude.Option.flatMap(json => Js.Json.decodeObject(json))
      |> Relude.Result.fromOption("JSON was not an object")
      |> Relude.Result.flatMap(dict =>
           ResultE.map2(
             (foo1, foo2) => {foo1, foo2},
             Js.Dict.get(dict, "foo1")
             |> Relude.Option.flatMap(Js.Json.decodeString)
             |> Relude.Result.fromOption("Failed to decode foo1"),
             Js.Dict.get(dict, "foo2")
             |> Relude.Option.flatMap(Js.Json.decodeString)
             |> Relude.Result.fromOption("Failed to decode foo2"),
           )
         );
    };
};

ReludeFetch.fetchWith(
  ~headers=
    Headers.authorizationBearer("mytoken")
    |> Headers.combine(Headers.acceptJson),
  "https://postman-echo.com/get?foo1=bar1&foo2=bar2",
)
//|> Relude.IO.tap(resp => Js.log(resp))
>>= ReludeFetch.Response.Json.decode(Data.decode)
|> Relude.IO.tap(json => Js.log(json))
|> Relude.IO.unsafeRunAsync(
     fun
     | Ok(data) => Js.log(Data.show(data))
     | Error(error) => Js.log(error),
   );