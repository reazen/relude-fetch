[%raw "require('isomorphic-fetch')"]

let _ =
  ReludeFetch.fetch("https://postman-echo.com/get?foo1=bar1&foo2=bar2")
  |> Relude.IO.unsafeRunAsync(fun
  | Ok(data) => Js.log(data)
  | Error(error) => Js.log(error)
  );