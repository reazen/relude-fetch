type fetchIO = Relude.IO.t(Fetch.response, Js.Promise.error);

let fetch: string => fetchIO =
  url => Relude.IO.suspendIO(() => Relude.Js.Promise.toIO(Fetch.fetch(url)));

let fetchWithInit: (string, Fetch.requestInit) => fetchIO =
  (url, init) =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithInit(url, init))
    );

let fetchWithRequest: Fetch.request => fetchIO =
  request =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithRequest(request))
    );

let fetchWithRequestInit: (Fetch.request, Fetch.requestInit) => fetchIO =
  (request, init) =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithRequestInit(request, init))
    );