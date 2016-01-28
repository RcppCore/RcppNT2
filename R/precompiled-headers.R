#' Pre-compile the RcppNT2 header
#'
#' Pre-compiles the \code{RcppNT2.h} header, for faster compilation. This can be
#' useful if you need to improve the speed of compilation when iterating with,
#' for example, \code{Rcpp::sourceCpp()}.
#'
#' Note that the precompiled header can be quite large (~400MB) so be sure that
#' you have ample disk space before precompiling the header.
#'
#' @export
precompileRcppNT2 <- function() {

  header <- system.file("include/RcppNT2.h", package = "RcppNT2")
  include <- system.file("include", package = "RcppNT2")
  output <- file.path(include, "RcppNT2.h.gch")

  R          <- file.path(R.home("bin"), "R")
  CXX        <- system(paste(shQuote(R), "CMD config CXX"), intern = TRUE)
  CXXFLAGS   <- system(paste(shQuote(R), "CMD config CXXFLAGS"), intern = TRUE)
  CXX1XFLAGS <- system(paste(shQuote(R), "CMD config CXX1XFLAGS"), intern = TRUE)

  cxxFlags <- if (nzchar(CXX1XFLAGS)) CXX1XFLAGS else CXXFLAGS

  cmd <- paste(
    CXX,
    "-x c++-header", header,
    paste("-I", include, sep = ""),
    paste("-I", R.home("include"), sep = ""),
    "-std=c++11",
    cxxFlags
  )

  message("Pre-compiling 'RcppNT2.h'...")
  status <- system(cmd)
  if (status || !file.exists(output))
    stop("Failed to compile 'RcppNT2.h'", call. = FALSE)

  message("Successfully compiled 'RcppNT2.h'.")
  invisible(output)
}
