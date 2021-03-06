//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SEVEN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Seven generic tag

     Represents the Seven constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Seven, double, 7
                                , 0x40e00000UL, 0x401c000000000000ULL
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Seven, Site> dispatching_Seven(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Seven, Site>();
   }
   template<class... Args>
   struct impl_Seven;
  }
  /*!
    Generates value 7

    @par Semantic:

    @code
    T r = Seven<T>();
    @endcode

    is similar to:

    @code
    T r = T(7);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Seven, Seven)
} }

#include <boost/simd/constant/common.hpp>

#endif
