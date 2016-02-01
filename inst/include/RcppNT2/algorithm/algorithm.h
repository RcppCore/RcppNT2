#ifndef RCPP_NT2_ALGORITHM_ALGORITHM_H
#define RCPP_NT2_ALGORITHM_ALGORITHM_H

#include <boost/simd/sdk/simd/algorithm.hpp>

namespace RcppNT2 {

template <typename T, typename U, typename UnOp>
U* simdTransform(const T* begin, const T* end, U* out, UnOp&& f)
{
  return boost::simd::transform(begin, end, out, std::forward<UnOp>(f));
}

template <typename T1, typename T2, typename U, typename BinOp>
U* simdTransform(const T1* begin1, const T1* end1, const T2* begin2, U* out, BinOp&& f)
{
  return boost::simd::transform(begin1, end1, begin2, out, std::forward<BinOp>(f));
}

template <typename T, typename U, typename F>
U simdAccumulate(const T* begin, const T* end, U init, F&& f)
{
  return boost::simd::accumulate(begin, end, init, std::forward<F>(f));
}

template <typename T, typename F>
F simdFor(const T* it, const T* end, F&& f)
{
  typedef boost::simd::pack<T> vT;
  static const std::size_t N = vT::static_size;
  const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
  const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;

  for (; it != aligned_begin; ++it)
    f(*it);

  for (; it != aligned_end; it += N)
    f(boost::simd::aligned_load<vT>(it));

  for (; it != end; ++it)
    f(*it);

  return std::forward<F>(f);
}

template <typename T1, typename T2, typename F>
F simdFor(const T1* begin1, const T1* end1, const T2* begin2, F&& f)
{
  typedef boost::simd::pack<T1> vT1;
  typedef boost::simd::pack<T2> vT2;

  static_assert(
    vT1::static_size == vT2::static_size,
    "T1 and T2 are not of the same size"
  );

  // Attempt to align on 'begin1', and use aligned loads
  // when feasible.
  static const std::size_t N = vT1::static_size;
  const T1* aligned_begin = std::min(boost::simd::align_on(begin1, N * sizeof(T1)), end1);
  const T1* aligned_end   = aligned_begin + (end1 - aligned_begin) / N * N;

  // Initial un-aligned region
  for (; begin1 != aligned_begin; ++begin1, ++begin2)
    f(*begin1, *begin2);

  // TODO: Somehow, profiling here suggested that using 'load'
  // rather than 'aligned_load' was actually faster (!?)
  for (; begin1 != aligned_end; begin1 += N, begin2 += N)
    f(boost::simd::load<vT1>(begin1), boost::simd::load<vT2>(begin2));

  // Final un-aligned region.
  for (; begin1 != end1; ++begin1, ++begin2)
    f(*begin1, *begin2);

  return f;
}

template <typename T, typename U, typename F>
U simdReduce(const T* begin, const T* end, U init, F&& f)
{
  return boost::simd::accumulate(begin, end, init, std::forward<F>(f));
}

template <typename T, typename U, typename MapReducer>
U simdMapReduce(const T* it, const T* end, U init, MapReducer&& f)
{
  // We separate the range into three regions, to allow
  // for aligned loads of data (when possible), and scalar
  // reads otherwise.
  //
  // --------- | ------- | ---------
  // unaligned | aligned | unaligned
  //
  //           ^ ------------------- aligned_begin
  //                     ^---------- aligned_end

  typedef boost::simd::pack<T> vT; // SIMD vector of T
  typedef boost::simd::pack<U> vU; // SIMD vector of U

  static const std::size_t N = vT::static_size;
  const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
  const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;

  // Buffer for the SIMD mapping operations
  vU buffer = boost::simd::splat<vU>(init);

  // Scalar operations for the initial unaligned region
  for (; it != aligned_begin; ++it)
    init = f.combine(f.map(*it), init);

  // Aligned, SIMD operations
  for (; it != aligned_end; it += N)
    buffer = f.combine(f.map(boost::simd::aligned_load<vT>(it)), buffer);

  // Reduce the buffer, joining it into the scalar vale
  init = f.combine(f.reduce(buffer), init);

  // Leftover unaligned region
  for (; it != end; ++it)
    init = f.combine(f.map(*it), init);

  return init;
}

} // namespace RcppParallel

#endif /* RCPP_NT2_ALGORITHM_ALGORITHM_H */
