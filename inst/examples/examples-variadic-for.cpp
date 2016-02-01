// Shows how 'simdFor()' can be used with an arbitrary
// number of input, output iterators.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

class DotProductAccumulator
{
public:
  // Implement a ternary call operator, that multiples
  // its three arguments together, and adds them up.
  template <typename T>
  void operator()(const T& a, const T& b, const T& c)
  {
    result_ += nt2::sum(a * b * c);
  }

  // Provide a 'double()' conversion operator so that
  // we can easily return the result from 'simdFor()'
  // See below for usage.
  operator double() const { return result_; }

private:
  double result_ = 0.0;
};

// [[Rcpp::export]]
double simdForTest(NumericVector a, NumericVector b, NumericVector c)
{
  return variadic::simdFor(DotProductAccumulator(), a, b, c);
}

/*** R
n <- 1024 * 1000
x <- rnorm(n)
y <- rnorm(n)
z <- rnorm(n)

stopifnot(all.equal(
  sum(x * y * z),
  simdForTest(x, y, z)
))

library(microbenchmark)
microbenchmark(
  R = sum(x * y * z),
  simd = simdForTest(x, y, z)
)
*/
