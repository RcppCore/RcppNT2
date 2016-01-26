//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MAX_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  max generic tag

      Represents the max function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct max_ : ext::elementwise_<max_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<max_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_max_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::max_, Site> dispatching_max_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::max_, Site>();
   }
   template<class... Args>
   struct impl_max_;
  }
  /*!
    Computes the largest of its parameter.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    T r = max(x, y);
    @endcode

    is similar to:

    @code
    T r =  if (x > y) ? x : y;
    @endcode

    @param  a0
    @param  a1

    @return an value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::max_, max, 2)
} }

#endif


