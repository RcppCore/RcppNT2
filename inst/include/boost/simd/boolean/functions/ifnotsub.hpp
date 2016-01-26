//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTSUB_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IFNOTSUB_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief ifnotsub generic tag

     Represents the ifnotsub function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ifnotsub_ : ext::elementwise_<ifnotsub_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ifnotsub_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ifnotsub_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::ifnotsub_, Site> dispatching_ifnotsub_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::ifnotsub_, Site>();
   }
   template<class... Args>
   struct impl_ifnotsub_;
  }
  /*!

    The function returns the second entry or the difference of the second
    and third entries, according to the first entry being True or
    False

    @par Semantic:

    For every parameters of types respectively T0, T1, T1:

    @code
    T1 r = ifnotsub(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T1 r = a0 ? a1 :  a1-a2;
    @endcode

    @par Alias:
    @c selnotadd

    @see @funcref{selsub}
    @param a0
    @param a1
    @param a2

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotsub_, ifnotsub, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifnotsub_, selnotsub,  3)
} }

#endif

