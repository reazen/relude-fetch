// Wrap all bs-fetch functions that return Js.Promise.t('a) to instead return Relude.IO.t('a, Js.Promise.error).
// Add the extra suspendIO in each case to ensure that Promises are not eagerly executed.

module Body = {
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

module Request = {
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

module Response = {
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

let fetch: string => Relude.IO.t(Fetch.response, Js.Promise.error) =
  url => Relude.IO.suspendIO(() => Relude.Js.Promise.toIO(Fetch.fetch(url)));

let fetchWithInit:
  (string, Fetch.requestInit) => Relude.IO.t(Fetch.response, Js.Promise.error) =
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