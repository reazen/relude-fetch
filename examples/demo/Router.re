[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let child =
    switch (url.path) {
    | ["fileUpload"] => <FileUploadDemo />
    | _ => React.null
    };

  <div>
    <h1> {React.string("Demos")} </h1>
    <a href="/fileUpload"> {React.string("File upload demo")} </a>
    child
  </div>;
};