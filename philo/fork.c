/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 22:45:40 by smun             ###   ########.fr       */
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
** Set philosopher's pickable and prioritied forks by its unique id.
*/

void	set_pickable_forks(int numbers, t_philo *philo, t_fork *forks)
{
	t_fork	*pickable_forks[2];
	t_fork	**sorted_forks;

	pickable_forks[kLeft] = &forks[(philo->unique_id + 0) % numbers];
	pickable_forks[kRight] = &forks[(philo->unique_id + 1) % numbers];
	sorted_forks = philo->pickable_forks;
	if (pickable_forks[kLeft]->unique_id > pickable_forks[kRight]->unique_id)
	{
		sorted_forks[0] = pickable_forks[kLeft];
		sorted_forks[1] = pickable_forks[kRight];
	}
	else
	{
		sorted_forks[0] = pickable_forks[kRight];
		sorted_forks[1] = pickable_forks[kLeft];
	}
}

/*
** Try to take forks. it fails if two pickable forks are duplicated.
*/

t_bool	fork_try_takes(t_fork *pickable_forks[])
{
	t_bool	success;

	if (pickable_forks[0]->unique_id == pickable_forks[1]->unique_id)
		return (FALSE);
	pthread_mutex_lock(&pickable_forks[0]->mutex);
	pthread_mutex_lock(&pickable_forks[1]->mutex);
	if (pickable_forks[0]->state == kNotUsing
		&& pickable_forks[1]->state == kNotUsing)
	{
		pickable_forks[0]->state = kUsing;
		pickable_forks[1]->state = kUsing;
		success = TRUE;
	}
	else
		success = FALSE;
	pthread_mutex_unlock(&pickable_forks[1]->mutex);
	pthread_mutex_unlock(&pickable_forks[0]->mutex);
	return (success);
}

void	fork_put_downs(t_fork *pickable_forks[])
{
	pthread_mutex_lock(&pickable_forks[0]->mutex);
	pthread_mutex_lock(&pickable_forks[1]->mutex);
	pickable_forks[0]->state = kNotUsing;
	pickable_forks[1]->state = kNotUsing;
	pthread_mutex_unlock(&pickable_forks[1]->mutex);
	pthread_mutex_unlock(&pickable_forks[0]->mutex);
}
