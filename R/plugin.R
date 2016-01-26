# Inline plugin used by 'Rcpp::sourceCpp()'.
inlineCxxPlugin <- function() {
  list(
    env = list(
      PKG_CXXFLAGS = paste("$(CXX1XSTD)")
    ),
    includes = "#include <RcppNt2.h>"
  )
}
