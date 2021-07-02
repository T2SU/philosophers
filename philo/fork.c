/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 16:16:26 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	fork_init(int unique_id, t_fork *fork)
{
	if (0 != pthread_mutex_init(&fork->mutex, NULL))
		return (FALSE);
	fork->unique_id = unique_id;
	return (TRUE);
}

/*
** Set philosopher's pickable and prioritized forks by unique id.
*/

void	prioritize_forks(int numbers, t_philo *philo, t_fork *forks)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &forks[(philo->unique_id + 0) % numbers];
	right_fork = &forks[(philo->unique_id + 1) % numbers];
	if ((philo->unique_id & 1) == 0)
	{
		philo->prioritized_forks[0] = right_fork;
		philo->prioritized_forks[1] = left_fork;
	}
	else
	{
		philo->prioritized_forks[0] = left_fork;
		philo->prioritized_forks[1] = right_fork;
	}
}

t_bool	fork_is_same(t_fork *forks[])
{
	return (forks[0]->unique_id == forks[1]->unique_id);
}

/*
** Try to take forks. it fails if two pickable forks are duplicated.
*/

t_bool	try_to_take_fork(t_philo *philo)
{
	t_fork	*fork;
	t_bool	success;

	fork = philo->prioritized_forks[philo->taken_forks];
	pthread_mutex_lock(&fork->mutex);
	if (fork->state == kNotTaken)
	{
		success = TRUE;
		fork->state = kTaken;
		philo->taken_forks++;
	}
	else
		success = FALSE;
	pthread_mutex_unlock(&fork->mutex);
	return (success);
}

void	put_down_forks(t_philo *philo)
{
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < 2)
	{
		fork = philo->prioritized_forks[i++];
		pthread_mutex_lock(&fork->mutex);
		fork->state = kNotTaken;
		pthread_mutex_unlock(&fork->mutex);
		philo->taken_forks = 0;
	}
}
