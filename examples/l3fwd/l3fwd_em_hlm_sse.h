/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2016 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __L3FWD_EM_HLM_SSE_H__
#define __L3FWD_EM_HLM_SSE_H__

#include "l3fwd_sse.h"

static __rte_always_inline void
get_ipv4_5tuple(struct rte_mbuf *m0, __m128i mask0,
		union ipv4_5tuple_host *key)
{
	 __m128i tmpdata0 = _mm_loadu_si128(
			rte_pktmbuf_mtod_offset(m0, __m128i *,
				sizeof(struct ether_hdr) +
				offsetof(struct ipv4_hdr, time_to_live)));

	key->xmm = _mm_and_si128(tmpdata0, mask0);
}

static inline void
get_ipv6_5tuple(struct rte_mbuf *m0, __m128i mask0,
		__m128i mask1, union ipv6_5tuple_host *key)
{
	__m128i tmpdata0 = _mm_loadu_si128(
			rte_pktmbuf_mtod_offset(m0, __m128i *,
				sizeof(struct ether_hdr) +
				offsetof(struct ipv6_hdr, payload_len)));

	__m128i tmpdata1 = _mm_loadu_si128(
			rte_pktmbuf_mtod_offset(m0, __m128i *,
				sizeof(struct ether_hdr) +
				offsetof(struct ipv6_hdr, payload_len) +
				sizeof(__m128i)));

	__m128i tmpdata2 = _mm_loadu_si128(
			rte_pktmbuf_mtod_offset(m0, __m128i *,
				sizeof(struct ether_hdr) +
				offsetof(struct ipv6_hdr, payload_len) +
				sizeof(__m128i) + sizeof(__m128i)));

	key->xmm[0] = _mm_and_si128(tmpdata0, mask0);
	key->xmm[1] = tmpdata1;
	key->xmm[2] = _mm_and_si128(tmpdata2, mask1);
}
#endif /* __L3FWD_EM_SSE_HLM_H__ */
