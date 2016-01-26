//==============================================================================
//         Copyright 2015 - J.T. Lapreste
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/round.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/copysign.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>
#include <boost/simd/include/functions/scalar/seldec.hpp>
#include <boost/simd/include/functions/scalar/ceil.hpp>
#include <boost/simd/include/functions/scalar/tenpower.hpp>
#include <boost/simd/include/constants/maxflint.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/dispatch/attributes.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( round_, tag::cpu_
                                    , (A0)
                                    , (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( round_, tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_ROUNDF
      return ::roundf(a0);
#else
      const result_type v = simd::abs(a0);
      if (!(v <=  Maxflint<result_type>()))
        return a0;
      result_type c =  boost::simd::ceil(v);
      return copysign(seldec(c-Half<result_type>() > v, c), a0);
#endif
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( round_, tag::cpu_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_ROUND
      return ::round(a0);
#else
      const result_type v = simd::abs(a0);
      if (!(v <=  Maxflint<result_type>()))
        return a0;
      result_type c =  boost::simd::ceil(v);
      return copysign(seldec(c-Half<result_type>() > v, c), a0);
#endif
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( round_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename  dispatch::meta::as_integer<A0>::type itype;
      A0 fac = tenpower(itype(a1));
      A0 tmp = round(a0*fac)/fac;
      return is_ltz(a1) ? round(tmp) : tmp;
    }
  };

} } }

#endif
