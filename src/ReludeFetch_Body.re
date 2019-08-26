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
    | Json(Js.Json.t)
    | Blob(Fetch.blob)
    | BufferSource(Fetch.bufferSource)
    | FormData(Fetch.formData)
    | UrlSearchParams(Fetch.urlSearchParams);

  let toBodyInit: t => Fetch.bodyInit =
    fun
    | String(str) => Fetch.BodyInit.make(str)
    | Json(json) => Fetch.BodyInit.make(Js.Json.stringify(json))
    | Blob(blob) => Fetch.BodyInit.makeWithBlob(blob)
    | BufferSource(bufferSource) =>
      Fetch.BodyInit.makeWithBufferSource(bufferSource)
    | FormData(formData) => Fetch.BodyInit.makeWithFormData(formData)
    | UrlSearchParams(urlSearchParams) =>
      Fetch.BodyInit.makeWithUrlSearchParams(urlSearchParams);
};

// These are probably not really needed - the Body module exists in bs-fetch as a mechanism to include
// these functions into the Request and Response modules

module Raw = {
  let arrayBuffer:
    Fetch.Body.t => Relude.IO.t(Fetch.arrayBuffer, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.arrayBuffer(body))
      );

  let blob: Fetch.Body.t => Relude.IO.t(Fetch.blob, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.blob(body))
      );

  let formData: Fetch.Body.t => Relude.IO.t(Fetch.formData, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.formData(body))
      );

  let json: Fetch.Body.t => Relude.IO.t(Js.Json.t, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.json(body))
      );

  let text: Fetch.Body.t => Relude.IO.t(string, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.text(body))
      );
};