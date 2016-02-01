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
 *    U init()                                Initial data state.
 *    T map(const T&... ts):                  Maps one or more values.
 *    T combine(const T& lhs, const T& rhs):  Combines two values.
 *    T reduce(const U& y):                   Reduces a SIMD pack to a scalar.
 */
class DotProductMapReducer
{
public:

  // Initial state of our data -- we're accumulating results in a 'double'
  // starting from 0, so use that.
  double init() { return 0.0; }

  // The transformation to be applied. Since we're computing the dot product,
  // we're performing an element-wise multiplication of the vectors passed
  // in. We'll just handle the two-element case here and multiply the two pieces.
  template <typename T>
  T map(const T& lhs, const T& rhs)
  {
    return lhs * rhs;
  }

  // How transformed values should be combined. Since we plan to just add them
  // up, we can express that computation as a simple sum.
  template <typename T>
  T combine(const T& lhs, const T& rhs)
  {
    return lhs + rhs;
  }

  // How should the SIMD pack structure be reduced? Similar to the above,
  // we just want to sum up the elements.
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

// We can also extend the 'PlusReducer' -- since we often reduce
// values by the sum, this simplifies our implementation. With
// this, we only need to express our map computation, as the
// PlusReducer will provide the requisite 'combine', 'reduce'
// and 'init' methods.
class DotProductMapReducerV2 : public reduce::PlusReducer
{
public:
  template <typename T>
  T map(const T& lhs, const T& rhs)
  {
    return lhs * rhs;
  }
};

// [[Rcpp::export]]
double simdDotProductV2(NumericVector x, NumericVector y)
{
  return variadic::simdMapReduce(DotProductMapReducerV2(), x, y);
}

/*** R
# Generate some data
set.seed(123)
x <- rnorm(1E6)
y <- rnorm(1E6)

# Ensure we produce the correct result
stopifnot(all.equal(sum(x * y), simdDotProduct(x, y)))
stopifnot(all.equal(sum(x * y), simdDotProductV2(x, y)))

# Benchmark
library(microbenchmark)
microbenchmark(
  R      = sum(x * y),
  simd   = simdDotProduct(x, y),
  simdV2 = simdDotProductV2(x, y)
)
*/
