path <- "inst/include/RcppNT2/functor/functor.h"
if (!dir.exists(dirname(path)))
  dir.create(dirname(path), recursive = TRUE, showWarnings = FALSE)

forEach <- function(data, f) {
   nm <- names(data)
   for (i in seq_along(data)) {
      f(nm[[i]], data[[i]])
   }
}

indent <- function(code, indent = "    ") {
   code <- paste(indent, code, sep = "")
   gsub("\n", "    \n", code, fixed = TRUE)
}

template <- paste(c(
   "#ifndef RCPP_NT2_FUNCTOR_FUNCTOR_H",
   "#define RCPP_NT2_FUNCTOR_FUNCTOR_H",
   "",
   "// Auto-generated functors for functions provided by NT2.",
   "// See 'gen/nt2-functors.R' for more details.",
   "",
   "namespace RcppNT2 {",
   "namespace functor {",
   "",
   "%s",
   "",
   "} // namespace functor",
   "} // namespace RcppNT2",
   "",
   "#endif /* RCPP_NT2_FUNCTOR_FUNCTOR_H */"
), collapse = "\n")

code <- NULL

unary <- list(
   sum  = c("sum(std::forward<T>(t))", "return sum(std::forward<T>(t));"),
   size = c("std::forward<T>(t).size()", "return std::forward<T>(t).size();")
)

unary_template <- paste(c(
   "struct %s {",
   "template <typename T>",
   "inline auto operator()(T&& t) -> decltype(%s)",
   "{",
   "%s",
   "}",
   "};",
   ""
), collapse = "\n")

forEach(unary, function(name, value) {
   code <<- c(code, sprintf(unary_template, name, value[[1]], indent(value[[2]])))
})

binary_code <- function(op) {
  forwarded <- sprintf("std::forward<%s>(%s)", c("T", "U"), c("t", "u"))
  pasted <- paste(forwarded, collapse = op)
  c(pasted, sprintf("return %s;", pasted))
}

binary <- list(
   plus   = binary_code(" + "),
   minus  = binary_code(" - "),
   times  = binary_code(" * "),
   divide = binary_code(" / ")
)

binary_template <- paste(c(
   "struct %s {",
   "template <typename T, typename U>",
   "inline auto operator()(T&& t, U&& u) -> decltype(%s)",
   "{",
   "%s",
   "}",
   "};",
   ""
), collapse = "\n")

forEach(binary, function(name, value) {
   code <<- c(code, sprintf(binary_template, name, value[[1]], indent(value[[2]])))
})

compiled <- sprintf(template, paste(code, collapse = "\n"))
cat(compiled, file = path, sep = "\n")
