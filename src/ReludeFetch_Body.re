module Type = {
  type t =
    | ArrayBuffer
    | Blob
    | FormData
    | Json
    | Text;

  let show: t => string =
    fun
    | ArrayBuffer => "ArrayBuffer"
    | Blob => "Blob"
    | FormData => "FormData"
    | Json => "Json"
    | Text => "Text;";
};

module Content = {
  type t =
    | String(string)
    | Json(Js.Json.t);

  let toBodyInit: t => Fetch.bodyInit =
    fun
    | String(str) => Fetch.BodyInit.make(str)
    | Json(json) => Fetch.BodyInit.make(Js.Json.stringify(json));
};

// These are probably not really needed - the Body module exists in bs-fetch as a mechanism to include
// these functions into the Request and Response modules

module Raw = {
  let asArrayBuffer:
    Fetch.Body.t => Relude.IO.t(Fetch.arrayBuffer, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.arrayBuffer(body))
      );

  let asBlob: Fetch.Body.t => Relude.IO.t(Fetch.blob, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.blob(body))
      );

  let asFormData:
    Fetch.Body.t => Relude.IO.t(Fetch.formData, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.formData(body))
      );

  let asJson: Fetch.Body.t => Relude.IO.t(Js.Json.t, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.json(body))
      );

  let asText: Fetch.Body.t => Relude.IO.t(string, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.text(body))
      );
};