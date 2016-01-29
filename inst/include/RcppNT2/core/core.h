#ifndef RCPP_NT2_CORE_CORE_H
#define RCPP_NT2_CORE_CORE_H

#include <RcppNT2/core/create.h>

namespace RcppNT2 {

template <typename T>
auto pbegin(T&& t) -> decltype(&std::forward<T>(t)[0])
{
  return &std::forward<T>(t)[0];
}

template <typename T>
auto pend(T&& t) -> decltype(&std::forward<T>(t)[0])
{
  return &std::forward<T>(t)[0] + std::forward<T>(t).size();
}

} // namespace RcppNT2

#endif /* RCPP_NT2_CORE_CORE_H */
