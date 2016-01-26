//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_NEGATENZ_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_NEGATENZ_HPP_INCLUDED

#include <boost/simd/ieee/functions/negatenz.hpp>
#include <boost/simd/include/functions/simd/bitofsign.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/signnz.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( negatenz_, tag::cpu_
                                    , (A0)
                                    , (generic_<arithmetic_<A0> >)
                                      (generic_<arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0*boost::simd::signnz(a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( negatenz_, tag::cpu_
                                    , (A0)
                                    , (generic_<floating_<A0> >)
                                      (generic_<floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_xor(bitofsign(a1), a0);
    }
  };

} } }
#endif
