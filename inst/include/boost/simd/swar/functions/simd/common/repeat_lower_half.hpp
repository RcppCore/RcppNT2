//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/swar/functions/repeat_lower_half.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/preprocessor/make.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( repeat_lower_half_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< unspecified_<A0>, X>))
                                    )
  {
    typedef A0                                    result_type;
    typedef simd::meta::cardinal_of<result_type>  card_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return eval(a0,typename card_t::type());
    }

    #define M0(z, n, t) extract<n %(card_t::value/2)>(a0)

    BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(1, M0)

    #undef M0
  };

  BOOST_DISPATCH_IMPLEMENT_IF         ( repeat_lower_half_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::simd::meta::is_bitwise_logical<A0> )
                                      , ((simd_< logical_<A0>, X>))
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return bitwise_cast<result_type>(
        repeat_lower_half( bitwise_cast<type>(a0) )
      );
    }
  };
} } }

#endif
