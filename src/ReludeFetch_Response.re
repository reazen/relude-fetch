module Raw = {
  let arrayBuffer:
    Fetch.Response.t => Relude.IO.t(Fetch.arrayBuffer, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.arrayBuffer(body))
      );

  let blob: Fetch.Response.t => Relude.IO.t(Fetch.blob, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.blob(body))
      );

  let formData:
    Fetch.Response.t => Relude.IO.t(Fetch.formData, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.formData(body))
      );

  let json: Fetch.Response.t => Relude.IO.t(Js.Json.t, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.json(body))
      );

  let text: Fetch.Response.t => Relude.IO.t(string, Js.Promise.error) =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.text(body))
      );
};

/**
Extracts an ArrayBuffer value from the response body, lifting any errors into the ReludeFetch Error type
*/
let arrayBuffer:
  Fetch.Response.t =>
  Relude.IO.t(Fetch.arrayBuffer, ReludeFetch_Error.t('decodeError)) =
  response => {
    let url = Fetch.Response.url(response);
    Raw.arrayBuffer(response)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.ArrayBuffer,
           innerError: e,
         })
       );
  };

/**
Extracts a Blob value from the response body, lifting any errors into the ReludeFetch Error type
*/
let blob:
  Fetch.Response.t =>
  Relude.IO.t(Fetch.blob, ReludeFetch_Error.t('decodeError)) =
  response => {
    let url = Fetch.Response.url(response);
    Raw.blob(response)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Blob,
           innerError: e,
         })
       );
  };

/**
Extracts a FormData value from the response body, lifting any errors into the ReludeFetch Error type
*/
let formData:
  Fetch.Response.t =>
  Relude.IO.t(Fetch.formData, ReludeFetch_Error.t('decodeError)) =
  response => {
    let url = Fetch.Response.url(response);
    Raw.formData(response)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.FormData,
           innerError: e,
         })
       );
  };

/**
Extracts a Js.Json.t value from the response body, lifting any errors into the ReludeFetch Error type
*/
let json:
  Fetch.Response.t =>
  Relude.IO.t(Js.Json.t, ReludeFetch_Error.t('decodeError)) =
  response => {
    let url = Fetch.Response.url(response);
    Raw.json(response)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Json,
           innerError: e,
         })
       );
  };

/**
Extracts a string value from the response body, lifting any errors into the ReludeFetch Error type
*/
let text:
  Fetch.Response.t => Relude.IO.t(string, ReludeFetch_Error.t('decodeError)) =
  response => {
    let url = Fetch.Response.url(response);
    Raw.text(response)
    |> Relude.IO.mapError(e =>
         ReludeFetch_Error.contentTypeError({
           url,
           expected: ReludeFetch_Body.Type.Text,
           innerError: e,
         })
       );
  };

/**
Response status code helpers
*/
module StatusCode = {
  /**
  Validates that the response status code is between min (inclusive) and max (exclusive)
  */
  let ensureRange =
      (~min: int, ~max: int, response: Fetch.Response.t)
      : Relude.IO.t(Fetch.Response.t, ReludeFetch_Error.t('decodeError)) => {
    let url = Fetch.Response.url(response);
    let code = Fetch.Response.status(response);
    code >= min && code < max
      ? Relude.IO.pure(response)
      : Relude.IO.throw(
          ReludeFetch_Error.statusError({url, actual: code, min, max}),
        );
  };

  /**
  Validates that the response status code is in the 2xx range
  */
  let ensure2xx = response => ensureRange(~min=200, ~max=300, response);
};

/**
Response JSON helpers
*/
module Json = {
  /**
  Extracts a Js.Json.t value from the response body, and attempts to decode it using the given decode function.
  Any errors are lifted into the common ReludeFetch Error type.
  */
  let decode:
    'a 'decodeError.
    (Js.Json.t => Belt.Result.t('a, 'decodeError), Fetch.Response.t) =>
    Relude.IO.t('a, ReludeFetch_Error.t('decodeError))
   =
    (decode, response) => {
      let url = Fetch.Response.url(response);
      json(response)
      |> Relude.IO.flatMap(json =>
           Relude.IO.fromResult(
             decode(json)
             |> Relude.Result.mapError(e =>
                  ReludeFetch_Error.decodeError({url, innerError: e})
                ),
           )
         );
    };
};