#ifndef RCPP_NT2_TRAITS_TRAITS_h
#define RCPP_NT2_TRAITS_TRAITS_h

template <int RTYPE> struct storage_type {};
template <> struct storage_type<REALSXP> { typedef double type; };
template <> struct storage_type<INTSXP>  { typedef int type; };

#endif /* RCPP_NT2_TRAITS_TRAITS_h */
