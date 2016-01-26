//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DEINTERLEAVE_FIRST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/deinterleave_first.hpp>
#include <boost/simd/swar/functions/details/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT         ( deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return details::shuffle<0, 2, 0, 2>(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT         ( deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return _mm_unpacklo_pd(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT         ( deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      result_type x = _mm_unpacklo_epi16(a0,a1);
      result_type y = _mm_unpackhi_epi16(a0,a1);

      return _mm_unpacklo_epi16 ( _mm_unpacklo_epi16(x,y)
                                , _mm_unpackhi_epi16(x,y)
                                );
    }
  };

  BOOST_DISPATCH_IMPLEMENT         ( deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return details::shuffle<0, 2, 0, 2>(a0,a1);
    }
  };

  BOOST_DISPATCH_IMPLEMENT         ( deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return  _mm_unpacklo_epi64( a0, a1 );
    }
  };

} } }

#endif
#endif
