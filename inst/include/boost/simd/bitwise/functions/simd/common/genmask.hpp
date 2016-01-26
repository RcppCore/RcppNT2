//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED

#include <boost/simd/bitwise/functions/genmask.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/simd/meta/is_logical_mask.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT         ( genmask_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<fundamental_<A0>,X>))
                            )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_zero(a0, Allbits<result_type>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT         ( genmask_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return genmask(is_nez(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT_IF         ( genmask_, tag::cpu_
                            , (A0)(X)
                            , (boost::simd::meta::is_logical_mask<A0>)
                            , ((simd_<logical_<A0>,X>))
                            )
  {
    typedef typename A0::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return bitwise_cast<typename A0::type>(a0);
    }
  };
} } }

#endif
