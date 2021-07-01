/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 20:56:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	sort_fork_by_priority(t_fork *pickable_forks[], t_fork *sorted[])
{
	if (pickable_forks[kLeft]->unique_id > pickable_forks[kRight]->unique_id)
	{
		sorted[0] = pickable_forks[kLeft];
		sorted[1] = pickable_forks[kRight];
	}
	else
	{
		sorted[0] = pickable_forks[kRight];
		sorted[1] = pickable_forks[kLeft];
	}
}

t_bool	fork_try_takes(t_fork *pickable_forks[])
{
	t_bool	success;

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
