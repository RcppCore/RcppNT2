//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>



namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief if_else_allbits generic tag

     Represents the if_else_allbits function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_else_allbits_ : ext::elementwise_<if_else_allbits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_else_allbits_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_if_else_allbits_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::if_else_allbits_, Site> dispatching_if_else_allbits_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::if_else_allbits_, Site>();
   }
   template<class... Args>
   struct impl_if_else_allbits_;
  }
  /*!
    If a0 is true returns a1 else returns allbits

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T r = if_else_allbits(a0,a1);
    @endcode

    is similar to:

    @code
    T r = a0 ? a1 : allbits;
    @endcode


    @par Alias:
    @c  if_else_nan,
    @c  ifelsenan,
    @c  ifnot_nan_else,
    @c  ifnotnanelse,
    @c  if_else_allbits,
    @c  ifelseallbits,
    @c  ifnot_allbits_else,
    @c  ifnotallbitselse,

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, if_else_nan, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifelsenan,   2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnot_nan_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnotnanelse, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, if_else_allbits, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifelseallbits,   2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnot_allbits_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_allbits_, ifnotallbitselse, 2)
} }

#endif


