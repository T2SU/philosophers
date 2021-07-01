/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:57:15 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 21:56:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

/*
** geeksforgeeks.org/multiply-number-10-without-using-multiplication-operator/
*/

static time_t	mul10(time_t n)
{
	return ((n << 1) + (n << 3));
}

/*
** https://stackoverflow.com/questions/5558492/divide-by-10-using-bit-shifts
*/

static time_t	div10(time_t n)
{
	time_t	q;
	time_t	r;

	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - (((q << 2) + q) << 1);
	return (q + (r > 9));
}

time_t	time_get(void)
{
	static time_t		start_s;
	static suseconds_t	start_us;
	struct timeval		t;
	time_t				seconds;
	suseconds_t			microseconds;

	gettimeofday(&t, NULL);
	if (!start_s)
	{
		start_s = t.tv_sec;
		start_us = t.tv_usec;
	}
	seconds = t.tv_sec - start_s;
	microseconds = t.tv_usec - start_us;
	return (mul10(mul10(mul10(seconds)))
		+ (div10(div10(div10(microseconds)))));
}
