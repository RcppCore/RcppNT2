//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_RSQRT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief fast_rsqrt generic tag

      Represents the fast_rsqrt function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_rsqrt_ : ext::elementwise_<fast_rsqrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_rsqrt_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fast_rsqrt_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::fast_rsqrt_, Site> dispatching_fast_rsqrt_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::fast_rsqrt_, Site>();
    }
    template<class... Args>
    struct impl_fast_rsqrt_;
  }
  /*!
    Computes the inverse of the square root its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = fast_rsqrt(x);
    @endcode

    is similar to:

    @code
    T r = T(1)/sqrt(x);
    @endcode

    @par Note:

    Fast means that the computation is possibly done through some
    low precision intrinsic. The result can be not fully accurate

    @see funcref{rsqrt}
    @param  a0

    @return      a value of the typeof the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_rsqrt_, fast_rsqrt, 1)
} }

#endif
