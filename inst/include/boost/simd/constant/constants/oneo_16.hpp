//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_16_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_16_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Oneo_16 generic tag

     Represents the Oneo_16 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_16, double, 0
                                , 0x3d800000LL, 0x3fb0000000000000ULL
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Oneo_16, Site> dispatching_Oneo_16(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Oneo_16, Site>();
   }
   template<class... Args>
   struct impl_Oneo_16;
  }
  /*!
    Generates value 1/16

    @par Semantic:

    @code
    T r = Oneo_16<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(16);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_16, Oneo_16)
} }

#include <boost/simd/constant/common.hpp>

#endif

