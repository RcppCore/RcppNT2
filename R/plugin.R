# Inline plugin used by 'Rcpp::sourceCpp()'.
inlineCxxPlugin <- function() {
  list(
    env = list(
      PKG_CXXFLAGS = paste(
        "$(CXX1XSTD)",
        "-include", system.file("include/RcppNT2.h", package = "RcppNT2")
      )
    ),
    includes = "#include <RcppNT2.h>"
  )
}
