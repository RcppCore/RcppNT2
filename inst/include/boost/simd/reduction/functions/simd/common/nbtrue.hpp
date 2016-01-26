//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_NBTRUE_HPP_INCLUDED

#include <boost/simd/reduction/functions/nbtrue.hpp>
#include <boost/simd/include/functions/simd/if_one_else_zero.hpp>
#include <boost/simd/include/functions/simd/sum.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( nbtrue_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<unspecified_<A0>,X>))
                                    )
  {
    typedef typename meta::as_arithmetic<A0>::type arith_t;
    typedef typename meta::scalar_of<arith_t>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return sum(if_one_else_zero(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( nbtrue_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_<unspecified_<A0>,X>))
                                      (scalar_< integer_<A1> > )
                                    )
  {
    typedef typename meta::as_arithmetic<A0>::type arith_t;
    typedef typename meta::scalar_of<arith_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const & a0, A1 const &) const
    {
      return sum(if_one_else_zero(a0));
    }
  };
} } }

#endif
