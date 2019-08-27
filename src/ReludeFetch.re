module Body = ReludeFetch_Body;
module Error = ReludeFetch_Error;
module FormData = ReludeFetch_FormData;
module Headers = ReludeFetch_Headers;
module Request = ReludeFetch_Request;
module Response = ReludeFetch_Response;

module Raw = {
  let fetch: string => Relude.IO.t(Fetch.response, Js.Promise.error) =
    url =>
      Relude.IO.suspendIO(() => Relude.Js.Promise.toIO(Fetch.fetch(url)));

  let fetchWithInit:
    (string, Fetch.requestInit) =>
    Relude.IO.t(Fetch.response, Js.Promise.error) =
    (url, init) =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.fetchWithInit(url, init))
      );

  let fetchWithRequest:
    Fetch.request => Relude.IO.t(Fetch.response, Js.Promise.error) =
    request =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.fetchWithRequest(request))
      );

  let fetchWithRequestInit:
    (Fetch.request, Fetch.requestInit) =>
    Relude.IO.t(Fetch.response, Js.Promise.error) =
    (request, init) =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.fetchWithRequestInit(request, init))
      );
};

/**
Issues a GET request to a URL
*/
let fetch: string => Relude.IO.t(Fetch.response, Error.t('decodeError)) =
  url =>
    Raw.fetch(url)
    |> Relude.IO.mapError(e => Error.fetchError({url, innerError: e}));

/**
Issues a request to a URL with additional request parameters.
*/
let fetchWithInit:
  (string, Fetch.requestInit) =>
  Relude.IO.t(Fetch.response, Error.t('decodeError)) =
  (url, init) =>
    Raw.fetchWithInit(url, init)
    |> Relude.IO.mapError(e => Error.fetchError({url, innerError: e}));

/**
Issues a request using a full request object.
*/
let fetchWithRequest:
  Fetch.request => Relude.IO.t(Fetch.response, Error.t('decodeError)) =
  request => {
    let url = Fetch.Request.url(request);
    Raw.fetchWithRequest(request)
    |> Relude.IO.mapError(e => Error.fetchError({url, innerError: e}));
  };

/**
Issues a request using a full request object and additional request parameters.
*/
let fetchWithRequestInit:
  (Fetch.request, Fetch.requestInit) =>
  Relude.IO.t(Fetch.response, Error.t('decodeError)) =
  (request, requestInit) => {
    let url = Fetch.Request.url(request);
    Raw.fetchWithRequestInit(request, requestInit)
    |> Relude.IO.mapError(e => Error.fetchError({url, innerError: e}));
  };

/**
Issues a request using the given optional parameters.
*/
let fetchWith =
    (
      ~method_: option(Fetch.requestMethod)=?,
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_?,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );

/**
Issues a GET request with the given optional parameters.
*/
let get =
    (
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Get,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );

/**
Issues a POST request with the given optional parameters.
*/
let post =
    (
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Post,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );

/**
Issues a PUT request with the given optional parameters.
*/
let put =
    (
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Put,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );

/**
Issues a PATCH request with the given optional parameters.
*/
let patch =
    (
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Patch,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );

/**
Issues a DELETE request with the given optional parameters.
*/
let delete =
    (
      ~headers: option(Headers.t)=?,
      ~body: option(Body.Content.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: option(Fetch.referrerPolicy)=?,
      ~mode: option(Fetch.requestMode)=?,
      ~credentials: option(Fetch.requestCredentials)=?,
      ~cache: option(Fetch.requestCache)=?,
      ~redirect: option(Fetch.requestRedirect)=?,
      ~integrity: option(string)=?,
      ~keepalive: option(bool)=?,
      url: string,
    )
    : Relude.IO.t('a, Error.t('decodeError)) =>
  fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Delete,
      ~headers=?Relude.Option.map(Headers.toHeadersInit, headers),
      ~body=?Relude.Option.map(Body.Content.toBodyInit, body),
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );