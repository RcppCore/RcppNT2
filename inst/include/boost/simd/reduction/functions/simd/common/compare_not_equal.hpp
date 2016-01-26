//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_NOT_EQUAL_HPP_INCLUDED

#include <boost/simd/reduction/functions/compare_not_equal.hpp>
#include <boost/simd/include/functions/simd/is_not_equal.hpp>
#include <boost/simd/include/functions/simd/any.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( compare_not_equal_
                                    , tag::cpu_, (X)(A0)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename meta::as_logical<typename A0::value_type>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::any(a0 != a1);
    }
  };
} } }

#endif
