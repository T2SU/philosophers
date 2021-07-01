/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:04:18 by smun              #+#    #+#             */
/*   Updated: 2021/06/30 19:36:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

int		main(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	suseconds_t first = time.tv_usec;
	for (int i = 0; i < 1; i++)
		usleep(1);
	gettimeofday(&time, NULL);
	suseconds_t end = time.tv_usec;
	printf("%u, %u, %u\n", first, end, end - first);
	return (0);
}

t_bool	init_forks(t_fork *fork)
{
	if (0 != pthread_mutex_init(&fork->mutex, NULL))
		return (FALSE);
	fork->state = kNotUsing;
	return (TRUE);
}

void	run_philosopher(t_philo *philo)
{

}

t_bool	init_philosopher(t_philo *philo)
{
}
