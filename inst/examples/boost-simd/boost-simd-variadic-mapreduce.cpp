// Perform a variadic map-reduce -- used to compute the
// dot product in a nice way.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

struct DotMapReducer
{
  double init() { return 0.0; }

  template <typename T>
  T map(const T& a, const T& b, const T& c)
  {
    return a * b * c;
  }

  template <typename T>
  T combine(const T& lhs, const T& rhs)
  {
    return lhs + rhs;
  }

  template <typename T>
  double reduce(const T& t)
  {
    return nt2::sum(t);
  }
};

// [[Rcpp::export]]
double simdDotVariadic(NumericVector a, NumericVector b, NumericVector c)
{
  return variadic::simdMapReduce(DotMapReducer(), a, b, c);
}

// [[Rcpp::export]]
double naiveDot(NumericVector a, NumericVector b, NumericVector c)
{
  double* pA = REAL(a);
  double* pB = REAL(b);
  double* pC = REAL(c);

  double* end = REAL(a) + a.size();

  double result = 0.0;
  for (; pA != end; ++pA, ++pB, ++pC)
    result += (*pA) * (*pB) * (*pC);

  return result;
}

/*** R
set.seed(123)
n <- 1000 * 1024
x <- rnorm(n); y <- rnorm(n); z <- rnorm(n)
stopifnot(all.equal(
  sum(x * y * z),
  simdDotVariadic(x, y, z)
))

library(microbenchmark)
microbenchmark(
  R = sum(x * y * z),
  simd = simdDotVariadic(x, y, z),
  naive = naiveDot(x, y, z)
)
*/
