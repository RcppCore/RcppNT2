//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENTM1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENTM1_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxexponentm1 generic tag

     Represents the Maxexponentm1 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxexponentm1 : ext::pure_constant_<Maxexponentm1>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxexponentm1> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Maxexponentm1( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponentm1::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,126> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponentm1::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,1022> {};

  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Maxexponentm1, Site> dispatching_Maxexponentm1(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Maxexponentm1, Site>();
   }
   template<class... Args>
   struct impl_Maxexponentm1;
  }
  /*!
    Generates the maximum exposant of floating point numbers minus one

    @par Semantic:

    @code
    as_integer<T> r = Maxexponentm1<T>();
    @endcode

    @code
    if T is double
      r =  1022;
    else if T is float
      r =  126;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxexponentm1, Maxexponentm1)
} }

#include <boost/simd/constant/common.hpp>

#endif
