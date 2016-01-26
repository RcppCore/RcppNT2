//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_TRUNC_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/arithmetic/functions/trunc.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/constants/maxflint.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT         ( trunc_
                                   , boost::simd::tag::sse_
                                   , (A0)
                                   , (scalar_< single_<A0> >)
                                   )
  {

    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      if (!(abs(a0) <=  Maxflint<result_type>()))
        return a0;
      return result_type(_mm_cvttss_si32(_mm_set_ss(a0)));
    }
  };

} } }

#endif
#endif
