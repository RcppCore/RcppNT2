// Demonstrates how NAs could be handled (removed)
// to allow for efficient SIMD computations. Uses
// this to compute the variance.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

struct IsNaN
{
  template <typename T>
  T operator()(const T& data)
  {
    return nt2::if_else(data == data, bitwise::ones(), bitwise::zeroes());
  }
};

struct NumNonZero
{
  template <typename T>
  void operator()(const T& t)
  {
    result_ += nt2::sum(nt2::if_else(t != 0.0, 1.0, 0.0));
  }

  operator double() const { return result_; }

  double result_ = 0.0;
};

class Sum
{
public:

  Sum() : result_(0.0) {}

  template <typename T>
  void operator()(const T& data, const T& mask)
  {
    result_ += nt2::sum(nt2::bitwise_and(data, mask));
  }

  operator double() const { return result_; }

private:
  double result_;

};

class SumOfSquares
{
public:
  explicit SumOfSquares(double mean)
    : mean_(mean), result_(0.0)
  {}

  template <typename T>
  void operator()(const T& data, const T& mask)
  {
    result_ += nt2::sum(nt2::sqr(nt2::bitwise_and(data - mean_, mask)));
  }

  operator double() const { return result_; }

private:
  double mean_;
  double result_;
};

// [[Rcpp::export]]
double simdVariance(NumericVector x)
{
  // Compute our NA bitmask. It's a vector o 'double's,
  // as we want to ensure SIMD 'double' x 'double'
  // instructions can be emitted when interacting with
  // our bitmask. Note that we use our 'begin' and 'end'
  // helpers
  std::vector<double> naMask(x.size());
  simdTransform(&x[0], &x[0] + x.size(), &naMask[0], IsNaN());

  // Using our bitmask, compute the number of non-NA elements.
  double N = simdFor(&naMask[0], &naMask[0] + naMask.size(), NumNonZero());

  // Compute the sum of our 'x' vector, discarding NAs.
  double total = simdFor(&x[0], &x[0] + x.size(), &naMask[0], Sum());

  // Compute our mean.
  double mean = total / N;

  // Now, compute squared deviations from that mean.
  double ssq = simdFor(&x[0], &x[0] + x.size(), &naMask[0], SumOfSquares(mean));

  // Divide by (n - 1), and we're done!
  return ssq / (N - 1);
}

/*** R
set.seed(123)

# Construct a vector filled with NAs.
n <- 1024 * 1000
x <- rnorm(n)
x[sample(n, n / 2)] <- NA

# Confirm we compute the correct variance.
stopifnot(all.equal(
  var(x, na.rm = TRUE),
  simdVariance(x)
))

# Check performance.
library(microbenchmark)
microbenchmark(
  R = var(x, na.rm = TRUE),
  C = simdVariance(x)
)
*/
