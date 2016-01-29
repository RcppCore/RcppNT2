#ifndef RCPP_NT2_BITWISE_BITWISE_H
#define RCPP_NT2_BITWISE_BITWISE_H

#include <utility>
#include <cstdint>

namespace RcppNT2 {
namespace bitwise {

namespace detail {

// Used for constructing 'double's with all bits set to 1.
union DoublePunner {
  uint64_t i;
  double d;
};

} // namespace detail

// A class which can be (lazily) converted to an integral value
// with all bits equal to 1. Primarily useful for 'double's.
// Intended use case:
//
//    double ones = bitwise::ones();
//    foo(static_cast<double>(bitwise::ones()));
//
class ones
{
public:

  operator double() const {
    detail::DoublePunner punner { -1ULL };
    return punner.d;
  }

  operator int() const {
    return ~0;
  }

};

class zeroes
{
public:
  template <typename T>
  operator T() const { return T(); }
};

} // namespace bitwise
} // namespace RcppNT2

#endif /* RCPP_NT2_BITWISE_BITWISE_H */
