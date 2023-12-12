open Jest;
open Expect;
open Relude.Js.Json.DSL;

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
  let baseURL = "https://jsonplaceholder.typicode.com";

  module Todo = {
    type t = {
      userId: int,
      id: int,
      title: string,
      completed: bool,
    };

    let todo1URL = baseURL ++ "/todos/1";

    let make = (userId, id, title, completed) => {
      userId,
      id,
      title,
      completed,
    };

    let decode: Js.Json.t => Belt.Result.t(t, string) =
      json => {
        make
        <$> JD.intFor("userId", json)
        <*> JD.intFor("id", json)
        <*> JD.stringFor("title", json)
        <*> JD.boolFor("completed", json)
        |> Relude.Result.fromValidation
        |> Relude.Result.mapError(_ => "Decode failed");
      };
  };
};

describe("ReludeFetch integration tests", () => {
  test("sync sanity check", () =>
    expect(true) |> toBe(true)
  );

  testAsync("async sanity check", onDone =>
    onDone(expect(true) |> toBe(true))
  );

  testAsync("fetch sample TODO", onDone => {
    let expectedTodo: Data.Todo.t = {
      userId: 1,
      id: 1,
      title: "delectus aut autem",
      completed: false,
    };

    ReludeFetch.fetchWith(
      ~headers=
        Headers.authorizationBearer("mytoken")
        |> Headers.combine(Headers.acceptJson),
      Data.Todo.todo1URL,
    )
    >>= ReludeFetch.Response.Json.decode(Data.Todo.decode)
    |> Relude.IO.tap(json => Js.log(json))
    |> Relude.IO.unsafeRunAsync(
         fun
         | Ok(actualTodo) =>
           onDone(expect(actualTodo) |> toEqual(expectedTodo))
         | Error(error) =>
           onDone(fail("Failed: " ++ Error.show(e => e, error))),
       );
  });
});
