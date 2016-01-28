#ifndef RCPP_NT2_CONVERT_WRAP_H
#define RCPP_NT2_CONVERT_WRAP_H

#include <R.h>
#include <Rinternals.h>

namespace RcppNT2 {
namespace convert {

#define RCPP_NT2_WRAP_MATRIX_IMPL(__CTYPE__, __SEXPTYPE__, __ACCESSOR__) \
SEXP wrap_matrix(const nt2::table<__CTYPE__>& data)                      \
{                                                                        \
  std::size_t n = nt2::numel(data);                                      \
  std::size_t nrow = nt2::size(data, 1);                                 \
  std::size_t ncol = nt2::size(data, 2);                                 \
                                                                         \
  SEXP result = Rf_allocMatrix(__SEXPTYPE__, nrow, ncol);                \
  ::memcpy(                                                              \
    (char*) __ACCESSOR__(result),                                        \
    (char*) data.begin(),                                                \
    sizeof(__CTYPE__) * n                                                \
  );                                                                     \
                                                                         \
  return result;                                                         \
}

RCPP_NT2_WRAP_MATRIX_IMPL(double, REALSXP, REAL);
RCPP_NT2_WRAP_MATRIX_IMPL(int,    INTSXP,  INTEGER);

#define RCPP_NT2_WRAP_VECTOR_IMPL(__CTYPE__, __SEXPTYPE__, __ACCESSOR__) \
SEXP wrap_vector(const nt2::table<__CTYPE__>& data)                      \
{                                                                        \
  std::size_t n = nt2::numel(data);                                      \
  SEXP result = Rf_allocVector(__SEXPTYPE__, n);                         \
  ::memcpy(                                                              \
    (char*) __ACCESSOR__(result),                                        \
    (char*) data.begin(),                                                \
    sizeof(__CTYPE__) * n                                                \
  );                                                                     \
  return result;                                                         \
}

RCPP_NT2_WRAP_VECTOR_IMPL(double, REALSXP, REAL);
RCPP_NT2_WRAP_VECTOR_IMPL(int,    INTSXP,  INTEGER);

#undef RCPP_NT2_WRAP_VECTOR_IMPL
#undef RCPP_NT2_WRAP_MATRIX_IMPL

} // namespace convert
} // namespace RcppNT2

namespace Rcpp {

SEXP wrap(const nt2::table<double>& data)
{
  std::size_t ndims = nt2::ndims(data);
  if (ndims == 1)
    return RcppNT2::convert::wrap_vector(data);
  else if (ndims == 2)
    return RcppNT2::convert::wrap_matrix(data);

  // TODO: wrap arbitrary arrays
  Rf_warning("cannot wrap nt2::table<T>s of dimension %i\n", (int) ndims);

  return R_NilValue;
}

} // namespace Rcpp

#endif /* RCPP_NT2_CONVERT_WRAP_H */
