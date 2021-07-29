/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:06:39 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 22:53:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

int	raise_error(const char *msg)
{
	int	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, "\n", 1);
	return (FALSE);
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
	if (t.tv_usec > start_us)
		microseconds = t.tv_usec - start_us;
	else if (seconds > 0)
	{
		seconds--;
		microseconds = 1000000 + t.tv_usec - start_us;
	}
	else
		microseconds = 0;
	return (seconds * 1000 + microseconds / 1000);
}

/*
** Not parsable int?
**   1.  2 or more '-'
**   2.  too big or too small number ( < -2147483648  or  > 2147483647)
**   3.  non digit or dash
**   4.  only dash '-'
*/

t_bool	ft_atoi_strict(const char *str, int *pvalue)
{
	size_t	i;
	t_bool	neg;
	int		temp;

	neg = str[0] == '-';
	i = neg;
	if (str[neg] == '\0')
		return (FALSE);
	*pvalue = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		temp = str[i++] - '0';
		if (neg)
			temp = -temp;
		temp = 10 * *pvalue + temp;
		if (temp != *pvalue && (temp < *pvalue) != neg)
			return (FALSE);
		*pvalue = temp;
	}
	return (TRUE);
}
