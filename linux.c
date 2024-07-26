/*
 *	TCP - Transmission Control Protocol
 *
 *	(c) 1999-2004 Tigran Aivazian <tigran@aivazian.fsnet.co.uk>
 *	(C) 2004 Andi Kleen, SuSE Labs
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/poll.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/skbuff.h>
#include <linux/scatterlist.h>
#include <linux/splice.h>
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/random.h>
#include <linux/bootmem.h>
#include <linux/highmem.h>
#include <linux/swap.h>
#include <linux/cache.h>
#include <linux/err.h>
#include <linux/crypto.h>
#include <linux/time.h>
#include <linux/slab.h>
#include <linux/uid_stat.h>

#include <net/icmp.h>
#include <net/tcp.h>
#include <net/xfrm.h>
#include <net/ip.h>
#include <net/sock.h>

#include "tcp.h"

int sysctl_tcp_timestamps __read_mostly = 1;
int sysctl_tcp_window_scaling __read_mostly = 1;
int sysctl_tcp_sack __read_mostly = 1;
int sysctl_tcp_fack __read_mostly = 1;
int sysctl_tcp_max_reordering __read_mostly = 300;
int sysctl_tcp_dsack __read_mostly = 1;
int sysctl_tcp_app_win __read_mostly = 31;
int sysctl_tcp_adv_win_scale __read_mostly = 2;
EXPORT_SYMBOL(sysctl_tcp_adv_win_scale);

/* Hook for UDP-Lite (RFC 3828) */
int sysctl_udplite_port_range_low __read_mostly;
int sysctl_udplite_port_range_high __read_mostly;

int sysctl_tcp_stdurg __read_mostly;
int sysctl_tcp_rfc1337 __read_mostly;
int sysctl_tcp_max_orphans __read_mostly = NR_FILE;
int sysctl_tcp_frto __read_mostly = 2;

int sysctl_tcp_thin_dupack __read_mostly;

int sysctl_tcp_moderate_rcvbuf __read_mostly = 1;
int sysctl_tcp_abc __read_mostly;

int sysctl_tcp_mtu_probing __read_mostly;
int sysctl_tcp_base_mss __read_mostly = TCP_BASE_MSS;

int sysctl_tcp_workaround_signed_windows __read_mostly = 0;

int sysctl_tcp_slow_start_after_idle __read_mostly = 1;

int sysctl_tcp_max_ssthresh __read_mostly = 0;
EXPORT_SYMBOL(sysctl_tcp_max_ssthresh);

int sysctl_tcp_thin_linear_timeouts __read_mostly;

int sysctl_tcp_keepalive_time __read_mostly = TCP_KEEPALIVE_TIME;
int sysctl_tcp_keepalive_probes __read_mostly = TCP_KEEPALIVE_PROBES;
int sysctl_tcp_keepalive_intvl __read_mostly = TCP_KEEPALIVE_INTVL;

int sysctl_tcp_syn_retries __read_mostly = TCP_SYN_RETRIES;
int sysctl_tcp_synack_retries __read_mostly = TCP_SYNACK_RETRIES;
int sysctl_tcp_retries1 __read_mostly = TCP_RETR1;
int sysctl_tcp_retries2 __read_mostly = TCP_RETR2;
int sysctl_tcp_orphan_retries __read_mostly;

static void tcp_push_pending_frames(struct sock *sk);

/* Adapt the MSS value used to make delayed ack decision to the
 * real world.
 */
static void tcp_measure_rcv_mss(struct sock *sk, const struct sk_buff *skb)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	const unsigned int lss = icsk->icsk_ack.last_seg_size;
	unsigned int len;

	icsk->icsk_ack.last_seg_size = 0;

	/* skb->len may jitter because of SACKs, even if peer
	 * sends good full-sized frames.
	 */
	len = skb_shinfo(skb)->gso_size ? : skb->len;
	if (len >= icsk->icsk_ack.rcv_mss) {
		icsk->icsk_ack.rcv_mss = len;
	} else {
		/* Otherwise, we make more careful check taking into account,
		 * that SACKs block is variable.
		 *
		 * "len" is invariant segment length, including TCP header.
		 */
		len += skb->data - skb_transport_header(skb);
		if (len >= TCP_MSS_DEFAULT + sizeof(struct tcphdr) ||
		    /* If PSH is not set, packet should be
		     * full sized, provided peer TCP is not badly broken.
		     * This observation (if it is correct 8)) allows
		     * to handle super-low mtu links fairly.
		     */
		    (len >= TCP_MIN_MSS + sizeof(struct tcphdr) &&
		     !(tcp_flag_word(tcp_hdr(skb)) & TCP_REMNANT))) {
			/* Receive mss is set to segment length, when peer
			 * advertises lower mss or this read is from
			 * repair queue.
			 */
			if (icsk->icsk_ack.advmss < len - sizeof(struct tcphdr) ||
			    tcp_is_skb_from_repair_queue(skb)) {
				icsk->icsk_ack.rcv_mss = len;
				icsk->icsk_ack.last_seg_size = len;
			}
			/* Otherwise, we still remember previous
			 * segments and the real MSS is obtained
			 * by averaging over all of them.
			 * This is invariant of SACKs.
			 */
		}
	}

	if (icsk->icsk_ack.rcv_mss > TCP_MSS_DEFAULT)
		icsk->icsk_ack.rcv_mss = TCP_MSS_DEFAULT;
}

static void tcp_update_rtt_min(struct sock *sk, const s32 rtt_us)
{
	u32 rtt_min = jiffies_to_usecs(tcp_sk(sk)->rtt_min);

	if (rtt_us <= 1)
		return;

	if (rtt_min == 0 || rtt_us < rtt_min)
		tcp_sk(sk)->rtt_min = usecs_to_jiffies(rtt_us);
}

static void tcp_check_adjust_rtt_min(struct sock *sk, struct tcp_sock *tp,
				     const s32 rtt_us)
{
	u32 min_rtt_us = jiffies_to_usecs(tp->rtt_min);

	if (rtt_us <= 1)
		return;

	if (min_rtt_us == 0 || rtt_us < min_rtt_us)
		tp->rtt_min = usecs_to_jiffies(rtt_us);
}

/* Calculate rto without backoff.  This is the second half of Van Jacobson's
 * routine referred to above.
 */
static void tcp_set_rto(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct dst_entry *dst = __sk_dst_get(sk);

	inet_csk(sk)->icsk_rto = __tcp_set_rto(tp);
	/* Do bound check. */
	if (inet_csk(sk)->icsk_rto > TCP_RTO_MAX)
		inet_csk(sk)->icsk_rto = TCP_RTO_MAX;
	/* Ensure the rto is not less than min_rto */
	if (dst) {
		u32 min_rto = dst_metric_rtt(dst, RTAX_RTO_MIN);

		if (min_rto > inet_csk(sk)->icsk_rto)
			inet_csk(sk)->icsk_rto = min_rto;
	}
}

__u32 tcp_init_cwnd(const struct tcp_sock *tp, const struct dst_entry *dst)
{
	__u32 cwnd = (dst ? dst_metric(dst, RTAX_INITCWND) : 0);

	if (!cwnd)
		cwnd = TCP_INIT_CWND;
	return min_t(__u32, cwnd, tp->snd_cwnd_clamp);
}

/* Set initial congestion window and parameters for all congestion control
 * algorithms.
 */
void tcp_init_congestion_control(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_congestion_ops *ca;

	ca = icsk->icsk_ca_ops;
	if (ca && ca->init)
		ca->init(sk);
}

static void tcp_session_reset_rwnd(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct dst_entry *dst;

	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	dst = __sk_dst_get(sk);
	if (dst) {
		u32 initmss = TCP_INIT_CWND * tcp_mss_to_mtu(sk, TCP_MSS_DEFAULT);
		u32 mtu = dst_mtu(dst);

		if (mtu < TCP_MIN_MSS)
			mtu = TCP_MIN_MSS;

		tp->snd_cwnd = min_t(__u32, initmss / mtu, TCP_INIT_CWND);
		tp->snd_cwnd_clamp = dst_metric(dst, RTAX_SSTHRESH);
	} else {
		/* No initial cwnd clamp, so initialize to default. */
		tp->snd_cwnd = TCP_INIT_CWND;
		tp->snd_cwnd_clamp = ~0;
	}

	tp->snd_cwnd_used = 0;
	tp->snd_cwnd_stamp = tcp_time_stamp;
	tp->prior_cwnd = tp->snd_cwnd;
	tp->prr_delivered = 0;
	tp->prr_out = 0;

	icsk->icsk_ca_state = TCP_CA_Open;
	icsk->icsk_ca_priv = NULL;
	tcp_init_congestion_control(sk);
}

/* Determine a window scaling and initial window to offer.
 * Based on the assumption that the given amount of space
 * will be offered. Store the results in the tp structure.
 * NOTE: for smooth operation initial space offering should
 * be a multiple of mss if possible. We assume here that mss >= 1.
 * This MUST be enforced by all callers.
 */
void tcp_select_initial_window(int __space, __u32 mss,
			       __u32 *rcv_wnd, __u32 *window_clamp,
			       int wscale_ok, __u8 *rcv_wscale,
			       __u32 init_rcv_wnd)
{
	unsigned int space = (__space < 0 ? 0 : __space);

	/* If no clamp set the clamp to the max possible scaled window */
	if (*window_clamp == 0)
		(*window_clamp) = (65535 << 14);
	space = min(*window_clamp, space);

	/* Quantize space offering to a multiple of mss if possible. */
	if (space > mss)
		space = (space / mss) * mss;

	/* NOTE: offering an initial window larger than 32767
	 * will break some buggy TCP stacks. If the admin tells us
	 * it is likely we could be speaking with such a buggy stack
	 * we will truncate our initial window offering to 32K-1
	 * unless the remote has sent us a window scaling option,
	 * which we interpret as a sign the remote TCP is not
	 * misinterpreting the window field as a signed quantity.
	 */
	if (sysctl_tcp_workaround_signed_windows)
		(*rcv_wnd) = min(space, MAX_TCP_WINDOW);
	else
		(*rcv_wnd) = space;

	(*rcv_wscale) = 0;
	if (wscale_ok) {
		/* Set window scaling on max possible window
		 * See RFC1323 for an explanation of the limit to 14
		 */
		space = max_t(u32, sysctl_tcp_rmem[2], sysctl_rmem_max);
		space = min_t(u32, space, *window_clamp);
		while (space > 65535 && (*rcv_wscale) < 14) {
			space >>= 1;
			(*rcv_wscale)++;
		}
	}

	/* Set initial window to a value enough for senders starting with
	 * initial congestion window of TCP_INIT_CWND. RFC5681 sec.3.1
	 */
	if (mss > (1 << *rcv_wscale)) {
		int init_cwnd = TCP_INIT_CWND;
		if (init_rcv_wnd)
			init_cwnd = min_t(u32, init_rcv_wnd, TCP_INIT_CWND);
		*rcv_wnd = max(*rcv_wnd, init_cwnd * mss);
	}

	/* Set the clamp no higher than max representable value */
	(*window_clamp) = min(65535U << (*rcv_wscale), *window_clamp);
}

/* Chose a new window to advertise, update state in tcp_sock for the
 * socket, and return result with RFC1323 scaling applied.  The return
 * value can be stuffed directly into th->window for an outgoing
 * frame.
 */
static u16 tcp_select_window(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(