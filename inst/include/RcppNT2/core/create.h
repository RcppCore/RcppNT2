#ifndef RCPP_NT2_CORE_CREATE_H
#define RCPP_NT2_CORE_CREATE_H

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

namespace RcppNT2 {

template <typename T, int RTYPE>
nt2::table<T> make_table_vector_impl(SEXP data)
{
  int n = Rf_length(data);

  T* ptr = reinterpret_cast<T*>(STRING_PTR(data));
  return nt2::table<T>(nt2::of_size(n, 1), ptr, ptr + n);
}

template <typename T, int RTYPE>
nt2::table<T> make_table_matrix_impl(SEXP data)
{
  int nr = Rf_nrows(data);
  int nc = Rf_ncols(data);
  int n = Rf_length(data);

  T* ptr = reinterpret_cast<T*>(STRING_PTR(data));
  return nt2::table<T>(nt2::of_size(nr, nc), ptr, ptr + n);
}

template <typename T, int RTYPE>
nt2::table<T> make_table_impl(SEXP data)
{
  if (Rf_isMatrix(data))
    return make_table_matrix_impl<T, RTYPE>(data);
  else
    return make_table_vector_impl<T, RTYPE>(data);
}

template <typename T>
nt2::table<T> make_table(SEXP data)
{
  switch (TYPEOF(data))
  {
  case REALSXP: return make_table_impl<double, REALSXP>(data);
  // case INTSXP:  return make_table_impl<int,    INTSXP>(data); // TODO: fails to compile?
  default:
    Rf_warning("can't create an 'nt2::table' from type '%s'", Rf_type2char(TYPEOF(data)));
  return nt2::table<T>();
  }
}

} // namespace RcppNT2

#endif /* RCPP_NT2_CORE_CREATE_H */
