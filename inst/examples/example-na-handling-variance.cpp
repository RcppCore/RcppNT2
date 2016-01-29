// Demonstrates how NAs could be handled (removed)
// to allow for efficient SIMD computations. Uses
// this to compute the variance.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

// A 'mask-aware' Sum class. The call operator accepts both
// 'data' and a 'mask' of the same time; one can use
// 'nt2::bitwise_and' to apply the mask. In our case, we'll
// have the mask set as bitwise '0' for NA', and bitwise '1'
// otherwise.
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

// A 'mask-aware' Sum of Squares class. As above, the
// call operator accepts both a 'data' and a 'mask'.
// We use 'nt2::bitwise_and' to apply the mask.
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
  // Use helpers to compute the NA bitmask, as well as
  // the number of non-NA elements in the vector.
  std::vector<double> naMask(x.size());
  std::size_t n;
  na::mask(pbegin(x), pend(x), pbegin(naMask), &n);

  // Compute the number of non-NA elements.
  std::size_t N = x.size() - n;

  // Compute the sum of our 'x' vector, discarding NAs.
  double total = simdFor(pbegin(x), pend(x), pbegin(naMask), Sum());

  // Compute our mean.
  double mean = total / N;

  // Now, compute squared deviations from that mean.
  double ssq = simdFor(pbegin(x), pend(x), pbegin(naMask), SumOfSquares(mean));

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
