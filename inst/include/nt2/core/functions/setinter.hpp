//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SETINTER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SETINTER_HPP_INCLUDED


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
      @brief setinter generic tag

      Represents the setinter function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct setinter_ : ext::unspecified_<setinter_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<setinter_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_setinter_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::setinter_, Site> dispatching_setinter_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::setinter_, Site>();
    }
    template<class... Args>
    struct impl_setinter_;
  }

  /*!
    Computes common elements to 2 tables with no repetitions as a column vector

    @par Semantic:

    For every tables expression

    @code
    auto r = setinter(a0, a1);
    @endcode

    returns the  datas as common to a0 and a1 with no repetitions as a column vector.

    @param a0
    �param a1

    @return a column vector of size less or equal to min(numel(a0), numel(a1))
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::setinter_       , setinter, 2)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::setinter_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::setinter_,Domain,N,Expr>
    : meta::size_as<Expr,0>
  {};

} }

#endif
