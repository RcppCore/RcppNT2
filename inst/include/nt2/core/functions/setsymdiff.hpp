//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SETSYMDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SETSYMDIFF_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief setsymdiff generic tag

      Represents the setsymdiff function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct setsymdiff_ : ext::unspecified_<setsymdiff_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<setsymdiff_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_setsymdiff_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::setsymdiff_, Site> dispatching_setsymdiff_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::setsymdiff_, Site>();
    }
    template<class... Args>
    struct impl_setsymdiff_;
  }

  /*!
    Computes elements from 2 tables that belongs to one of them but not to both,
    with no repetitions as a column vector

    @par Semantic:

    For every tables expression

    @code
    auto r = setsymdiff(a0, a1);
    @endcode

    returns the  symmetric difference of the datas contained in the two table expressions as a column vector.

    @param a0
    �param a1

    @return a column vector of size less or equal to min(numel(a0), numel(a1))
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::setsymdiff_       , setsymdiff, 2)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::setsymdiff_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::setsymdiff_,Domain,N,Expr>
    : meta::size_as<Expr,0>
  {};

} }

#endif
