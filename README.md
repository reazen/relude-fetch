# relude-fetch

[![GitHub CI](https://img.shields.io/github/workflow/status/reazen/relude-fetch/CI/master)](https://github.com/reazen/relude-fetch/actions)
[![npm](https://img.shields.io/npm/v/relude-fetch.svg)](https://www.npmjs.com/package/relude-fetch)

## Overview

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

## Examples

See the [tests](https://github.com/reazen/relude-fetch/blob/master/__tests__/ReludeFetch_test.re) for example usage.

Also see the [demo](https://github.com/reazen/relude-fetch/blob/master/examples/demo) for real-world usage, such as file uploads.

## Developer info

### Installation

Dependencies of this library are listed as `peerDepenencies` to avoid issues with multiple version
errors with npm's installation methodology combined with BuckleScript.

```
> npm install --save bs-bastet relude bs-fetch relude-fetch

# Add bs-bastet, relude, bs-fetch, and relude-fetch to your bsconfig.json
```

### Scripts

```
# Normal development scripts
> npm run clean
> npm run build
> npm run cleanbuild
> npm run test
> npm run cleantest
> npm run watch

# Run the demo project via parcel
> npm run demo
```

### Publishing to npm

```
> npm version major|minor|patch
> git push origin --follow-tags
> git push upstream --follow-tags
> npm publish
```

### NixOS

```
> nix-shell
%nix%> npm install
```
