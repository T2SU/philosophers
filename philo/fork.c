/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 14:25:04 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	fork_init(int unique_id, t_fork *fork)
{
	if (0 != pthread_mutex_init(&fork->mutex, NULL))
		return (FALSE);
	fork->state = kNotUsing;
	fork->unique_id = unique_id;
	return (TRUE);
}

/*
** Set philosopher's pickable and prioritized forks by unique id.
*/

void	prioritize_forks_to_pick(int numbers, t_philo *philo, t_fork *forks)
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

t_bool	fork_try_to_take(t_fork *fork)
{
	t_bool	success;

	pthread_mutex_lock(&fork->mutex);
	if (fork->state == kNotUsing)
	{
		fork->state = kUsing;
		success = TRUE;
	}
	else
		success = FALSE;
	pthread_mutex_unlock(&fork->mutex);
	return (success);
}

void	fork_put_down(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->state = kNotUsing;
	pthread_mutex_unlock(&fork->mutex);
}
