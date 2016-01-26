//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_LOGEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_LOGEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Logeps generic tag

     Represents the Logeps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Logeps, double, 1
                                , 0xc17f1402UL, 0xc04205966f2b4f19ULL
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Logeps, Site> dispatching_Logeps(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Logeps, Site>();
   }
   template<class... Args>
   struct impl_Logeps;
  }
  /*!
    Generates the  logarithm of the machine epsilon.

    @par Semantic:

    @code
    T r = Logeps<T>();
    @endcode

    is similar to:

    @code
      r =  log(Eps<T>());
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Logeps, Logeps)
} }

#include <boost/simd/constant/common.hpp>

#endif
