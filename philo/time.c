/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:57:15 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 21:58:46 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

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
	return (seconds * 1000 + microseconds / 1000);
}
