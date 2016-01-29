#ifndef RCPP_NT2_NA_NA_H
#define RCPP_NT2_NA_NA_H

#include <RcppNT2/bitwise/bitwise.h>

namespace RcppNT2 {
namespace na {

namespace detail {

struct Masker
{
  template <typename T>
  T operator()(const T& data)
  {
    static const double ones   = bitwise::ones();
    static const double zeroes = bitwise::zeroes();
    return nt2::if_else(data == data, ones, zeroes);
  }
};

struct MaskerWithCount
{

  template <typename T>
  T operator()(const T& data)
  {
    static const double ones   = bitwise::ones();
    static const double zeroes = bitwise::zeroes();
    auto&& compare = data == data;
    count_ += nt2::sum(nt2::if_else(compare, 1.0, 0.0));
    return nt2::if_else(compare, ones, zeroes);
  }

  std::size_t count() { return count_; }
  std::size_t count_ = 0;
};

struct Counter
{
  template <typename T>
  void operator()(const T& t)
  {
    count_ += nt2::sum(t != t);
  }

  template <typename T>
  operator T() const { return T(count_); }

  std::size_t count_ = 0;
};

} // namespace detail

template <typename T, typename U>
void mask(const T* begin, const T* end, U* out)
{
  simdTransform(begin, end, out, detail::Masker());
}

template <typename T, typename U, typename V>
void mask(const T* begin, const T* end, U* out, V* count)
{
  detail::MaskerWithCount masker;
  simdTransform(begin, end, out, std::reference_wrapper<detail::MaskerWithCount>(masker));
  *count = masker.count();
}

template <typename T>
std::size_t count(const T& t)
{
  return simdReduce(pbegin(t), pend(t), std::size_t(0), detail::Counter());
}

} // namespace na
} // namespace RcppNT2

#endif /* RCPP_NT2_NA_NA_H */
