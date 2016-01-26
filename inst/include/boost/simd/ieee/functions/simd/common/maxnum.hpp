//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MAXNUM_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MAXNUM_HPP_INCLUDED

#include <boost/simd/ieee/functions/maxnum.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( maxnum_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::max(a0, a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( maxnum_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type lA0;
      const lA0 cond = is_nan(a0);
      const A0 a = if_else(cond,a0,a1);
      const A0 b = if_else(cond,a1,a0);
      return boost::simd::max(a, b);
    }
  };

} } }

#endif
