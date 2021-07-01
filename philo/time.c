/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:57:15 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 18:29:52 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

suseconds_t	time_get(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec * 1000);
}
