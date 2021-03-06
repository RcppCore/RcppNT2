//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ZERO_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Zero generic tag

     Represents the Zero constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Zero, double , 0, 0, 0 )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Zero, Site> dispatching_Zero(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Zero, Site>();
   }
   template<class... Args>
   struct impl_Zero;
  }
  /*!
    Generates value 0

    @par Semantic:

    @code
    T r = Zero<T>();
    @endcode

    is similar to:

    @code
    T r = T(0);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Zero, Zero)
} }

#include <boost/simd/constant/common.hpp>

#endif
