[%raw "require('isomorphic-fetch')"];

module Data = {
  type t = {
    foo1: string,
    foo2: string,
  };

  let show = data => "{foo1:" ++ data.foo1 ++ ", foo2:" ++ data.foo2 ++ "}";

  let decode: Js.Json.t => Belt.Result.t(t, string) =
    _json => Ok({foo1: "bar1", foo2: "bar2"});
};

module Error = {
  type error =
    | APIError(Js.Promise.error)
    | ParseError(Js.Promise.error)
    | DecodeError(string);

  module Type: BsAbstract.Interface.TYPE with type t = error = {
    type t = error;
  };
};

module InfixMonad = Relude.IO.Infix.Monad(Error.Type);

let (>>=) = InfixMonad.(>>=);

let _ =
  ReludeFetch.fetch("https://postman-echo.com/get?foo1=bar1&foo2=bar2")
  |> Relude.IO.mapError(e => Error.APIError(e))
  >>= (
    response =>
      ReludeFetch.Response.json(response)
      |> Relude.IO.mapError(e => Error.ParseError(e))
  )
  |> Relude.IO.tap(json => Js.log(json))
  >>= (
    json =>
      Relude.IO.fromResult(Data.decode(json))
      |> Relude.IO.mapError(e => Error.DecodeError(e))
  )
  |> Relude.IO.unsafeRunAsync(
       fun
       | Ok(data) => Js.log(Data.show(data))
       | Error(error) => Js.log(error),
     );