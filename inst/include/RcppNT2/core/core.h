#ifndef RCPP_NT2_CORE_CORE_H
#define RCPP_NT2_CORE_CORE_H

namespace RcppNT2 {

template <typename T>
auto begin(T&& t) -> decltype(&std::forward<T>(t)[0])
{
  return &std::forward<T>(t)[0];
}

template <typename T>
auto end(T&& t) -> decltype(&std::forward<T>(t)[0])
{
  return &std::forward<T>(t)[0] + std::forward<T>(t).size();
}

} // namespace RcppNT2

#endif /* RCPP_NT2_CORE_CORE_H */
