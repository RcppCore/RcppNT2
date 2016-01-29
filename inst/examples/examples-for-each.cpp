// Showcases how a stateful functor can be used with `simdFor()`,
// for arbitrary operations over a range of values.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

class ProductAccumulator
{
public:

   ProductAccumulator() : result_(1.0) {}

   template <typename T>
   void operator()(const T& data)
   {
      result_ *= nt2::prod(data);
   }

   operator double() const {
      return result_;
   }

private:
   double result_;
};

// [[Rcpp::export]]
double simdProd(NumericVector x) {
   return simdFor(x.begin(), x.end(), ProductAccumulator());
}

/*** R
x <- 1:16
stopifnot(all.equal(prod(x), simdProd(x)))
*/
