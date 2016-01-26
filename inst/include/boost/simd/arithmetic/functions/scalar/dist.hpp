//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIST_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIST_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/dist.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( dist_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a0>a1) ? a0-a1 : a1-a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( dist_, tag::cpu_
                                    , (A0)
                                    , (scalar_<floating_<A0> >)
                                      (scalar_<floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::abs(a0 - a1);
    }
  };
} } }

#endif
