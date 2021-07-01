/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 20:39:46 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	fork_try_take(t_fork *fork)
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
