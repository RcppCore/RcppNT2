//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_IS_EQUAL_HPP_INCLUDED

#include <boost/simd/operator/functions/is_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT ( is_equal_, tag::cpu_
                                    , (A0)
                                    , (scalar_< bool_<A0> >)
                                      (scalar_< bool_<A0> >)
                                    )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a0 == a1);
    }
  };
  BOOST_DISPATCH_IMPLEMENT ( is_equal_, tag::cpu_
                                    , (A0)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< fundamental_<A0> >)
                                    )
  {
    typedef typename simd::meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(a0 == a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT ( is_equal_, tag::cpu_
                                    , (A0)
                                    , (scalar_< logical_<A0> >)
                                      (scalar_< logical_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(a0 == a1);
    }
  };
} } }


#endif
