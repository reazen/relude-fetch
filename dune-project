(lang dune 3.8)

(generate_opam_files)

(using melange 0.1)

(source
 (github reazen/relude-fetch))

(name relude-fetch)

(license "MIT")

(maintainers "Michael Martin" "Andy White")

(authors "Michael Martin" "Andy White")

(homepage https://github.com/reazen/relude-fetch)

(bug_reports https://github.com/reazen/relude-fetch/issues)

(package
 (name relude-fetch)
 (synopsis "Relude Fetch")
 (description "Relude interop library for the fetch API")
 (depends
  dot-merlin-reader
  (melange
   (>= 2.0.0))
  (ocaml
   (>= 5.1.0))
  (reason
   (>= 3.10.0))
  ocaml-lsp-server
  relude
  bastet
  (melange-jest
   (>= 0.1.0))
  opam-check-npm-deps
  melange-fetch
  melange-jest))
