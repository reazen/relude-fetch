/**
 * FormData support for fetch, mostly borrowed from this bs-fetch pull request:
 *
 * https://github.com/reasonml-community/bs-fetch/pull/14
 *
 * At the time of this writing, this pull request has been sitting open for like 6 months, seemingly abandoned.
 */;

/**
 * Minimal binding to the JS File API `File` type
 *
 * Copied from here:  https://github.com/reasonml-community/bs-webapi-incubator/blob/master/src/Webapi/Webapi__File.re
 *
 * I'm copying this definition here, because I don't want to add a dependency on bs-webapi-incubator in this project.
 * The webapi project doesn't seem to have a complete implementation of anything related to FormData, File, etc.
 */
module File = {
  type t;

  [@mel.get] external name: t => string = "name";
  [@mel.get] external type_: t => string = "type";
  [@mel.get] external size: t => float = "size";
  //[@mel.get] external preview: t => string = "";

  /**
   * Unsafely coerces this value into a value of a desired type.  Useful for passing
   * essentially untyped/unchecked data across API boundaries.
   */
  let unsafeCoerceTo: t => 'a = Relude.Unsafe.coerce;

  /**
   * Unsafely coerces any value into a value of this type.  Useful for passing
   * essentially untyped/unchecked data across API boundaries.
   */
  let unsafeCoerceFrom: 'a => t = Relude.Unsafe.coerce;
};

module Blob = {
  type t = Fetch.blob;

  /**
   * Unsafely coerces this value into a value of a desired type.  Useful for passing
   * essentially untyped/unchecked data across API boundaries.
   */
  let unsafeCoerceTo: t => 'a = Relude.Unsafe.coerce;

  /**
   * Unsafely coerces any value into a value of this type.  Useful for passing
   * essentially untyped/unchecked data across API boundaries.
   */
  let unsafeCoerceFrom: 'a => t = Relude.Unsafe.coerce;
};

/**
 * Minimal binding for the JS "FormData" type
 */
type t = Fetch.formData;

/**
 * Creates a new (mutable) FormData object
 *
 * ```reasonml
 * let formData = FormData.make();
 * ```
 */
[@mel.new]
external make: unit => t = "FormData";

/**
 * Appends a JS object to the FormData for the given key
 *
 * ```reasonml
 * let myObject = ...; // Get a Js.t({..}) value (?)
 * let formData = FormData.make();
 * FormData.appendObject(formData, "myKey", myObject); // mutates
 * ```
 */
[@mel.send]
external appendObject: (t, string, Js.t({..})) => unit = "append";

/**
 * Appends a blob value to the FormData for the given key
 *
 * ```reasonml
 * let myBlob = ...; // Get a blob (?)
 * let formData = FormData.make();
 * FormData.appendBlob(formData, "myKey", myBlob); // mutates
 * ```
 */
[@mel.send]
external appendBlob: (t, string, Blob.t) => unit = "append";

/**
 * Appends a string value to the FormData for the given key
 *
 * ```reasonml
 * let formData = FormData.make();
 * FormData.appendString(formData, "myKey", "myValue"); // mutates
 * ```
 */
[@mel.send]
external appendString: (t, string, string) => unit = "append";

/**
 * Appends a file to the FormData for the given key
 *
 * ```reasonml
 * // Get event (e.g. from an onChange or onSubmit listener in ReasonReact)
 * let event: ReactEvent.Form.t = ...;
 *
 * // Get the associated <input type="file"/> element from the event
 * let inputElement: Js.t({..}) = ReactEvent.Form.target(e); // Everything is basically untyped in this API...
 *
 * // Get the files from the <input type="file" /> - this is an untyped cast
 * let files: array(File.t) = inputElement##files;
 *
 * // Create the mutable FormData
 * let formData = FormData.make();
 *
 * // Add the files
 * files => Relude.Array.forEach(file =>
 *   FormData.appendFile(formData, file |> File.name, file) // mutates
 * );
 * ```
 */
[@mel.send]
external appendFile: (t, string, File.t) => unit = "append";

/**
 * Sets an object value in the FormData, overwriting any existing key
 */
[@mel.send]
external setObject: (t, string, Js.t({..})) => unit = "set";

/**
 * Sets an blob value in the FormData, overwriting any existing key
 */
[@mel.send]
external setBlob: (t, string, Blob.t) => unit = "set";

/**
 * Sets a string value in the FormData, overwriting any existing key
 */
[@mel.send]
external setString: (t, string, string) => unit = "set";

/**
 * Sets a File.t value in the FormData, overwriting any existing key
 */
[@mel.send]
external setFile: (t, string, File.t) => unit = "set";

/**
 * Deletes a key from the FormData
 */
[@mel.send]
external delete: (t, string) => unit = "delete";
