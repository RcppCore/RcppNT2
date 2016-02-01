// Shows how 'simdMapReduce()' can be used to compute the dot product of a set of vectors.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

/**
 * 'simdMapReduce()' expects an object implementing a number of templated
 * methods:
 *
 * U init()                                Initial data state.
 * T map(const T&... ts):                  Maps one or more values.
 * T combine(const T& lhs, const T& rhs):  Combines two values.
 * T reduce(const U& y):                   Reduces a SIMD pack to a scalar.
 */
class DotProductMapReducer
{
public:

  double init() { return 0.0; }

  template <typename T>
  T map(const T& lhs, const T& rhs)
  {
    return lhs * rhs;
  }

  template <typename T>
  T combine(const T& lhs, const T& rhs)
  {
    return lhs + rhs;
  }

  template <typename T>
  auto reduce(const T& t) -> decltype(nt2::sum(t))
  {
    return nt2::sum(t);
  }
};

// [[Rcpp::export]]
double simdDotProduct(NumericVector x, NumericVector y)
{
  return variadic::simdMapReduce(DotProductMapReducer(), x, y);
}

/*** R
x <- rnorm(1E6)
y <- rnorm(1E6)
stopifnot(all.equal(sum(x * y), simdDotProduct(x, y)))

library(microbenchmark)
microbenchmark(
  R    = sum(x * y),
  simd = simdDotProduct(x, y)
)
*/
