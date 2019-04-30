module IO = {
  type error = Js.Promise.error;

  type t('a) = Relude.IO.t('a, error);

  type response = t(Fetch.response);
  type arrayBuffer = t(Fetch.arrayBuffer);
  type blob = t(Fetch.blob);
  type formData = t(Fetch.formData);
  type json = t(Js.Json.t);
  type text = t(string);

  type mapError('e) = error => 'e;
};

module Body = {
  type t = Fetch.Body.t;

  let arrayBuffer: t => IO.arrayBuffer =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.arrayBuffer(body))
      );

  let blob: t => IO.blob =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.blob(body))
      );

  let formData: t => IO.formData =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.formData(body))
      );

  let json: t => IO.json =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.json(body))
      );

  let text: t => IO.text =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Body.text(body))
      );
};

module Request = {
  type t = Fetch.Request.t;

  let arrayBuffer: t => IO.arrayBuffer =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.arrayBuffer(body))
      );

  let blob: t => IO.blob =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.blob(body))
      );

  let formData: t => IO.formData =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.formData(body))
      );

  let json: t => IO.json =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.json(body))
      );

  let text: t => IO.text =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Request.text(body))
      );
};

module Response = {
  type t = Fetch.Response.t;

  let arrayBuffer: t => IO.arrayBuffer =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.arrayBuffer(body))
      );

  let blob: t => IO.blob =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.blob(body))
      );

  let formData: t => IO.formData =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.formData(body))
      );

  let json: t => IO.json =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.json(body))
      );

  let text: t => IO.text =
    body =>
      Relude.IO.suspendIO(() =>
        Relude.Js.Promise.toIO(Fetch.Response.text(body))
      );
};

let fetch: string => IO.response =
  url => Relude.IO.suspendIO(() => Relude.Js.Promise.toIO(Fetch.fetch(url)));

let fetchWithInit: (string, Fetch.requestInit) => IO.response =
  (url, init) =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithInit(url, init))
    );

let fetchWithRequest: Fetch.request => IO.response =
  request =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithRequest(request))
    );

let fetchWithRequestInit: (Fetch.request, Fetch.requestInit) => IO.response =
  (request, init) =>
    Relude.IO.suspendIO(() =>
      Relude.Js.Promise.toIO(Fetch.fetchWithRequestInit(request, init))
    );