//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_TOUINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_TOUINTS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/arithmetic/functions/touints.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( touints_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return vec_ctu(a0(),0);
    }
  };
} } }

#endif
#endif
