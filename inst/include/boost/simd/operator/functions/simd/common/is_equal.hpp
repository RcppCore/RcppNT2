//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_EQUAL_HPP_INCLUDED

#include <boost/simd/operator/functions/is_equal.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT_IF         ( is_equal_
                                      , boost::simd::tag::cpu_
                                      , (A0)(X)
                                      , (mpl::equal_to< mpl::sizeof_<A0>
                                                      , mpl::sizeof_<typename A0::type>
                                                      >
                                        )
                                      , ((simd_<logical_<A0>,X>))
                                        ((simd_<logical_<A0>,X>))
                                      )
  {
    typedef A0                                                result_type;
    typedef typename meta::as_arithmetic<A0>::type            base_t;
    typedef typename dispatch::meta::as_integer<base_t>::type cast_t;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<A0> ( eq( bitwise_cast<cast_t>(a0)
                                  , bitwise_cast<cast_t>(a1)
                                  )
                              );
    }
  };
} } }

#endif
