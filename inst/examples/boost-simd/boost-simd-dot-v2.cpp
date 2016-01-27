// Shows how 'simdMapReduce()' could be used to compute
// the dot product of two vectors.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

struct DotProduct
{
public:
  DotProduct()
    : packed_(0.0), result_(0.0)
  {}

  void operator()(double lhs, double rhs)
  {
    result_ += lhs * rhs;
  }

  void operator()(const boost::simd::pack<double>& lhs,
                  const boost::simd::pack<double>& rhs)
  {
    packed_ += lhs * rhs;
  }

  operator double() const {
    return result_ + sum(packed_);
  }

private:
  boost::simd::pack<double> packed_;
  double result_;
};

// [[Rcpp::export]]
double simdDot(NumericVector lhs, NumericVector rhs)
{
  return simdFor(lhs.begin(), lhs.end(), rhs.begin(), DotProduct());
}

/*** R
set.seed(123)
n <- 1024 * 1000
lhs <- rnorm(n)
rhs <- rnorm(n)
stopifnot(all.equal(sum(lhs * rhs), simdDot(lhs, rhs)))

library(microbenchmark)
microbenchmark(
  simd = simdDot(lhs, rhs),
  R    = sum(lhs * rhs)
)
*/
