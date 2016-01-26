// Showcases how a stateful functor can be used with `simdFor()`,
// for arbitrary operations over a range of values.

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

// Product of squared deviations
class Accumulator
{
public:
   
   Accumulator() : result_(1.0) {}
   
   template <typename T>
   void operator()(const T& data)
   {
      result_ *= boost::simd::prod(data);
   }
   
   operator double() const {
      return result_;
   }
   
private:
   double result_;
};

// [[Rcpp::export]]
double simdProd(NumericVector x) {
   return simdFor(x.begin(), x.end(), Accumulator());
}

/*** R
x <- 1:16
stopifnot(all.equal(prod(x), simdProd(x)))
*/