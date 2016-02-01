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
    f(*it, *ts...);

  for (; it != aligned_end; increment<N>(it, ts...))
    f(boost::simd::load<vT>(it), boost::simd::load<vT>(ts)...);

  for (; it != end; increment<1>(it, ts...))
    f(*it, *ts...);

  return std::forward<F>(f);

}

template <typename F, typename T, typename... Ts>
F simdFor(F&& f, const T& t, const Ts&... ts)
{
  return simdFor(std::forward<F>(f), pbegin(t), pend(t), pbegin(ts)...);
}

template <typename MapReducer, typename U, typename T, typename... Ts>
U simdMapReduce(MapReducer&& f, U init, const T* it, const T* end, const Ts*... ts)
{
  typedef boost::simd::pack<T> vT; // SIMD vector of T
  typedef boost::simd::pack<U> vU; // SIMD vector of U

  static const std::size_t N = vT::static_size;
  const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
  const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;

  // Buffer for the SIMD mapping operations
  vU buffer = boost::simd::splat<vU>(init);

  // Scalar operations for the initial unaligned region
  for (; it != aligned_begin; increment<1>(it, ts...))
    init = f.combine(f.map(*it, *ts...), init);

  // Aligned, SIMD operations
  for (; it != aligned_end; increment<N>(it, ts...))
    buffer = f.combine(
      f.map(boost::simd::aligned_load<vT>(it), boost::simd::load<vT>(ts)...),
      buffer
    );

  // Reduce the buffer, joining it into the scalar vale
  init = f.combine(f.reduce(buffer), init);

  // Leftover unaligned region
  for (; it != end; increment<1>(it, ts...))
    init = f.combine(f.map(*it, *ts...), init);

  return init;
}

template <typename MapReducer, typename T, typename... Ts>
auto simdMapReduce(MapReducer&& reducer, const T& t, const Ts&... ts)
  -> decltype(std::forward<MapReducer>(reducer).init())
{
  return simdMapReduce(std::forward<MapReducer>(reducer),
                       std::forward<MapReducer>(reducer).init(),
                       pbegin(t),
                       pend(t),
                       pbegin(ts)...);
}


} // namespace variadic
} // namespace RcppNT2

#endif /* RCPP_NT2_VARIADIC_VARIADIC_H */
