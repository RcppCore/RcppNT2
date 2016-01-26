//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FALSE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FALSE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief False generic tag

     Represents the False constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct False : ext::pure_constant_<False>
    {
      typedef logical<double> default_type;
      typedef ext::pure_constant_<False> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_False( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::False, Site> dispatching_False(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::False, Site>();
   }
   template<class... Args>
   struct impl_False;
  }
  /*!
    Generates the value False as a logical associated to chosen type

    @par Semantic:

    @code
    logical<T> r = False<T>();
    @endcode

    is similar to:

    @code
    auto r = logical<T>(false);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::False, False)
} }

#include <boost/simd/constant/common.hpp>

#endif
