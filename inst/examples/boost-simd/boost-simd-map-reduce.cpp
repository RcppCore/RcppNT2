// Shows how 'simdMapReduce()' can be used to efficiently
// transform and accumulate values.

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

class SumOfSquaresReducer
{
public:

   explicit SumOfSquaresReducer(double mean)
      : mean_(mean)
   {}

   template <typename T>
   void map(const T& self, T* pBuffer)
   {
      *pBuffer += nt2::sqr(self - mean_);
   }

   template <typename T, typename U>
   void reduce(const T& data, U* pBuffer)
   {
      *pBuffer += nt2::sum(data);
   }

private:
   double mean_;
};

// [[Rcpp::export]]
double simdVar(NumericVector x)
{
   double total = simdReduce(x.begin(), x.end(), 0.0, functor::plus());
   double n = x.size();
   double mean = total / n;

   double ssq = simdMapReduce(x.begin(), x.end(), 0.0, SumOfSquaresReducer(mean));

   return ssq / (n - 1);
}

/*** R
set.seed(123)
x <- rnorm(1024)
stopifnot(all.equal(var(x), simdVar(x)))
library(microbenchmark)
microbenchmark(var(x), simdVar(x))
*/
