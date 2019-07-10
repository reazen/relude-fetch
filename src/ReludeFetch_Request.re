module Raw = {
  let arrayBuffer:
    Fetch.Request.t => Relude.IO.t(Fetch.arrayBuffer, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.arrayBuffer(body))
      );

  let blob: Fetch.Request.t => Relude.IO.t(Fetch.blob, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.blob(body))
      );

  let formData:
    Fetch.Request.t => Relude.IO.t(Fetch.formData, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.formData(body))
      );

  let json: Fetch.Request.t => Relude.IO.t(Js.Json.t, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.json(body))
      );

  let text: Fetch.Request.t => Relude.IO.t(string, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.text(body))
      );
};

/**
Extracts an ArrayBuffer value from the request body, lifting any errors into the ReludeFetch Error type
*/
let arrayBuffer:
  Fetch.Request.t =>
  Relude.IO.t(Fetch.arrayBuffer, ReludeFetch_Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.arrayBuffer(request)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.ArrayBuffer,
           innerError: e,
         })
       );
  };

/**
Extracts a Blob value from the request body, lifting any errors into the ReludeFetch Error type
*/
let blob:
  Fetch.Request.t =>
  Relude.IO.t(Fetch.blob, ReludeFetch_Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.blob(request)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Blob,
           innerError: e,
         })
       );
  };

/**
Extracts a FormData value from the request body, lifting any errors into the ReludeFetch Error type
*/
let formData:
  Fetch.Request.t =>
  Relude.IO.t(Fetch.formData, ReludeFetch_Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.formData(request)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.FormData,
           innerError: e,
         })
       );
  };

/**
Extracts a Js.Json.t value from the request body, lifting any errors into the ReludeFetch Error type
*/
let json:
  Fetch.Request.t =>
  Relude.IO.t(Js.Json.t, ReludeFetch_Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.json(request)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Json,
           innerError: e,
         })
       );
  };

/**
Extracts a string value from the request body, lifting any errors into the ReludeFetch Error type
*/
let text:
  Fetch.Request.t => Relude.IO.t(string, ReludeFetch_Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.text(request)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Text,
           innerError: e,
         })
       );
  };