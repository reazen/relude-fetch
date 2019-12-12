open Relude.Globals;
module FormData = ReludeFetch.FormData;
module File = FormData.File;

////////////////////////////////////////////////////////////////////////////////
// This kind of stuff would usually live outside the component (e.g. in an API module)
////////////////////////////////////////////////////////////////////////////////

module API = {
  // Defines our API error type
  module Error = {
    type t = ReludeFetch.Error.t(string);
    let show = error => ReludeFetch.Error.show(a => a, error);
    module Type = {
      type nonrec t = t;
    };
  };

  // Open the IO infix operators
  module IOE = IO.WithError(Error.Type);
  open IOE.Infix;

  // Function to upload a file in IO
  let uploadFile = (file: File.t): IO.t(unit, Error.t) => {
    // Setup the FormData
    let formData = FormData.make();
    FormData.appendFile(formData, "myFile", file);
    FormData.appendString(formData, "someOtherKey", "someValue");

    // Note: no need to set enctype/content-type/etc. - the browser seems to do it automatically
    // This call fails, but you can inspect the request in the dev tools to see that it has the
    // multi-part encoded form data.
    ReludeFetch.fetchWith(
      ~method__=Fetch.Post,
      ~body=FormData(formData),
      "/fake-upload-file",
    )
    >>= ReludeFetch.Response.StatusCode.ensure2xx
    $> ();
  };
};

////////////////////////////////////////////////////////////////////////////////
// Component-specific stuff
////////////////////////////////////////////////////////////////////////////////

type state = {
  file: option(File.t),
  message: option(string),
};

let initialState = {file: None, message: None};

type action =
  | SetFile(File.t)
  | Submit
  | SubmitSuccess
  | SubmitFailure(API.Error.t);

let onFileInputChange = (send: action => unit, event: ReactEvent.Form.t): unit => {
  let input: Js.t({..}) = ReactEvent.Form.target(event);
  let files: array(File.t) = input##files;
  let fileOpt: option(File.t) = Array.head(files);
  fileOpt |> Option.forEach(file => send(SetFile(file)));
};

let onSubmit = (send: action => unit, event: ReactEvent.Form.t): unit => {
  ReactEvent.Form.preventDefault(event);
  send(Submit);
};

[@react.component]
let make = () => {
  let (state, send) =
    ReludeReact.Reducer.useReducer(
      (state, action) =>
        switch (action) {
        | SetFile(file) =>
          Update({
            file: Some(file),
            message: Some("Selected file: " ++ (file |> File.name)),
          })

        | Submit =>
          switch (state.file) {
          | None => Update({...state, message: Some("No file selected")})
          | Some(file) =>
            UpdateWithIO(
              {
                ...state,
                message: Some("Uploading file: " ++ (file |> File.name)),
              },
              API.uploadFile(file)
              |> IO.bimap(_ => SubmitSuccess, error => SubmitFailure(error)),
            )
          }

        | SubmitSuccess =>
          Update({...state, message: Some("Upload success!")})

        | SubmitFailure(error) =>
          Update({
            ...state,
            message: Some("Upload error: " ++ API.Error.show(error)),
          })
        },
      initialState,
    );

  <div>
    <h1> {React.string("File upload demo")} </h1>
    <p>
      {React.string(
         "Open the browser dev tools to see the request - the fetch call will fail as there is no server to accept the request.",
       )}
    </p>
    <form onSubmit={onSubmit(send)}>
      <input type_="file" onChange={onFileInputChange(send)} />
      <br />
      <br />
      <button type_="submit"> {React.string("Submit")} </button>
    </form>
    <span> {React.string(state.message |> Option.getOrElse(""))} </span>
  </div>;
};