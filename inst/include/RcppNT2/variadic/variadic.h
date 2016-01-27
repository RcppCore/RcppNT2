#ifndef RCPP_NT2_VARIADIC_VARIADIC_H
#define RCPP_NT2_VARIADIC_VARIADIC_H

#include <RcppNT2/variadic/tools.h>

namespace RcppNT2 {
namespace variadic {

template <typename F, typename T, typename... Ts>
F simdFor(F&& f, const T* it, const T* end, const Ts*... ts)
{
  typedef boost::simd::pack<T> vT;
  static const std::size_t N = vT::static_size;

  const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
  const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;

  for (; it != aligned_begin; increment<1>(it, ts...))
    std::forward<F>(f)(*it, *ts...);

  for (; it != aligned_end; increment<N>(it, ts...))
    std::forward<F>(f)(boost::simd::load<vT>(it), boost::simd::load<vT>(ts)...);

  for (; it != end; increment<1>(it, ts...))
    std::forward<F>(f)(*it, *ts...);

  return f;

}

template <typename F, typename T, typename... Ts>
F simdFor(F&& f, const T& t, const Ts&... ts)
{
  return simdFor(std::forward<F>(f), t.begin(), t.end(), begin(ts)...);
}

} // namespace variadic
} // namespace RcppNT2

#endif /* RCPP_NT2_VARIADIC_VARIADIC_H */
