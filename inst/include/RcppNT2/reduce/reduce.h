#ifndef RCPP_NT2_REDUCE_REDUCE_h
#define RCPP_NT2_REDUCE_REDUCE_h

namespace RcppNT2 {
namespace reduce {

template <typename V = double>
class PlusReducer
{
public:
  V init() { return V{}; }

  template <typename T>
  T combine(const T& t)
  {
    return t;
  }

  template <typename T, typename... Rest>
  T combine(const T& t, const Rest&... rest)
  {
    return t + combine(rest...);
  }

  template <typename T>
  auto reduce(const T& t) -> decltype(nt2::sum(t))
  {
    return nt2::sum(t);
  }
};

} // namespace reduce

template <typename T>
using PlusReducer = reduce::PlusReducer<T>;

} // namespace RcppNT2

#endif /* RCPP_NT2_REDUCE_REDUCE_h */
