//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELDEC_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELDEC_HPP_INCLUDED

#include <boost/simd/boolean/functions/seldec.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( seldec_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_<fundamental_<A0>, X>))
                                      ((simd_<integer_<A1>, X>))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return a1 + bitwise_cast<A1>(genmask(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( seldec_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_<fundamental_<A0>, X>))
                                      ((simd_<arithmetic_<A1>, X>))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return selsub(a0, a1, One<A1>());
    }
  };
} } }
#endif
