/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:08:27 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 19:06:04 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>

static t_mutex		*get_print_mutex(void)
{
	static t_mutex	mutex;

	return (&mutex);
}

t_bool				print_init(void)
{
	if (0 != pthread_mutex_init(get_print_mutex(), NULL))
		return (FALSE);
	return (TRUE);
}

void				print_uninit(void)
{
	pthread_mutex_destroy(get_print_mutex());
}

void				print_state(int unique_id, int state, const time_t time)
{
	t_mutex			*mutex;

	mutex = get_print_mutex();
	pthread_mutex_lock(mutex);
	if (state == kEating)
		printf("%ld %d is eating\n", time, unique_id);
	else if (state == kSleeping)
		printf("%ld %d is sleeping\n", time, unique_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, unique_id);
	else if (state == kDead)
		printf("%ld %d is died\n", time, unique_id);
	pthread_mutex_unlock(mutex);
}

void				print_fork(int unique_id, const time_t time)
{
	t_mutex			*mutex;

	mutex = get_print_mutex();
	pthread_mutex_lock(mutex);
	printf("%ld %d has taken a fork\n", time, unique_id);
	pthread_mutex_unlock(mutex);
}
