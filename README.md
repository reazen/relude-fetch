# relude-fetch

[Relude](https://github.com/reazen/relude) interop library for the Browser
[Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API).
This can also be used in Node.js using a polyfill like
[isomorphic-fetch](https://www.npmjs.com/package/isomorphic-fetch).

This library basically wraps the
[bs-fetch](https://github.com/reasonml-community/bs-fetch) Bucklescript library
to lift any publicly-exposed `Js.Promise.t('a)` values into `Relude.IO.t('a,
Js.Promise.error)` values.  Using `IO` rather than `Promise` makes error
handling 100% more explicit, allows for better composability with other
effect and error types, and unlocks the full power of monads!

See the [demo](https://github.com/reazen/relude-fetch/blob/master/examples/Demo.re) for
example usage.