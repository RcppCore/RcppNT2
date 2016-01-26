// The 'hello world' of Boost.SIMD, showing how packs can be
// used and manipulated at a low level.
//
// See: http://nt2.metascale.fr/doc/html/tutorials/simd_hello_world.html

// [[Rcpp::depends(RcppNT2)]]
#include <RcppNT2.h>
using namespace RcppNT2;

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
void HelloWorld()
{
   typedef boost::simd::pack<float> p_t;

   p_t res;
   p_t u(10);
   p_t r = boost::simd::splat<p_t>(11);

   res = (u + r) * 2.f;

   Rcout << res << std::endl;
}

/*** R
HelloWorld()
*/
