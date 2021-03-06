//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REC_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/rec.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/if_one_else_zero.hpp>
#include <boost/simd/include/functions/simd/if_else_allbits.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( rec_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<uint_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_allbits(a0, if_one_else_zero(a0 == One<A0>()));
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( rec_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<int_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(a0, if_else_zero(abs(a0) == One<A0>(), a0), Valmax<A0>());
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( rec_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return One<result_type>()/a0;
    }
  };
} } }

#endif
