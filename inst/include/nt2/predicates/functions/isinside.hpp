//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISINSIDE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISINSIDE_HPP_INCLUDED

/*!
  @file
  @brief Defines the isinside function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for isinside functor
    **/
    struct isinside_ : ext::abstract_<isinside_>
    {
      typedef ext::abstract_<isinside_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_isinside_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::isinside_, Site> dispatching_isinside_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::isinside_, Site>();
    }
    template<class... Args>
    struct impl_isinside_;
  }

  /*!
    @brief Is an expression

    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isinside_, isinside, 2)

  /*!
    @brief Is an expression

    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isinside_, isinside, 3)
}

#endif