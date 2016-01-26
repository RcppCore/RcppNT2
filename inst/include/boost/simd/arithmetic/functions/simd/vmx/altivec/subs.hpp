//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_SUBS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_SUBS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/arithmetic/functions/subs.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( subs_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_< int_<A0>
                                            , boost::simd::tag::vmx_
                                            >
                                      ))
                                      ((simd_< int_<A0>
                                            , boost::simd::tag::vmx_
                                            >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_subs( a0(), a1() );
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( subs_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_< uint_<A0>
                                            , boost::simd::tag::vmx_
                                            >
                                      ))
                                      ((simd_< uint_<A0>
                                            , boost::simd::tag::vmx_
                                            >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_subs( a0(), a1() );
    }
  };
} } }

#endif
#endif
