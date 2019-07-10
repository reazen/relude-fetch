/**
Contains headers for a HTTP request or response
*/
type t =
  | Headers(Js.Dict.t(string));

/**
Empty header set
*/
let empty: t = Headers(Js.Dict.empty());

/**
Combines two header sets into a single set
*/
let combine: (t, t) => t =
  (Headers(a), Headers(b)) => {
    let dictAdd = (key, value, dict) =>
      Js.Dict.set(dict, key, value) |> Relude.Function.const(dict);

    let dictCombine = (a, b) =>
      Js.Dict.entries(b)
      |> Relude.Array.foldLeft((dict, (k, v)) => dictAdd(k, v, dict), a);

    Headers(dictCombine(a, b));
  };

/**
Converts a header set into the Fetch.HeadersInit.t type
*/
let toHeadersInit: t => Fetch.HeadersInit.t =
  (Headers(dict)) => Fetch.HeadersInit.makeWithDict(dict);

/**
Converts a key/value pair into a header set
*/
let fromKeyValue: (Js.Dict.key, string) => t =
  (key, value) => Headers(Js.Dict.fromList([(key, value)]));

/* TODO: need to base 64 encode the user/pass
   let authorizationBasic: (string, string) => t =
     (username, password) =>
       fromKeyValue("Authorization", "Basic " ++ username ++ ":" ++ password);
   */

/**
Creates an Authorization: Bearer header with the given token
*/
let authorizationBearer: string => t =
  token => fromKeyValue("Authorization", "Bearer " ++ token);

/**
Creates an "Accept: application/json" header
*/
let acceptJson: t = fromKeyValue("Accept", "application/json");

/**
Creates a "Content-Type: application/json" header
*/
let contentTypeJson: t = fromKeyValue("Content-Type", "application/json");

/**
Semigroup instance for Headers
*/
module Semigroup: BsAbstract.Interface.SEMIGROUP with type t = t = {
  type nonrec t = t;
  let append = combine;
};

/**
Monoid instance for Headers
*/
module Monoid: BsAbstract.Interface.MONOID with type t = t = {
  include Semigroup;
  let empty = empty;
};