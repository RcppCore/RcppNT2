// Example using 'nt2::sin()'.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

struct nt2_sin {
   template <typename T>
   T operator()(const T& data) {
      return nt2::sin(data);
   }
};

// [[Rcpp::export]]
NumericVector nt2Sin(NumericVector input) {
   NumericVector output = no_init(input.size());
   simdTransform(input.begin(), input.end(), output.begin(), nt2_sin());
   return output;
}

/*** R
set.seed(123)
data <- rnorm(1024 * 1000)
stopifnot(all.equal(sin(data), nt2Sin(data)))

library(microbenchmark)
microbenchmark(
   R = sin(data),
   nt2 = nt2Sin(data)
)
*/
