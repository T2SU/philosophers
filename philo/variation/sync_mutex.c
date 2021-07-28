/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:20:28 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 00:27:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

/*
** Mutual exclusion (Mut-ex) and critical section.
** Mutex is a locking mechanism.
**   In an environment where multiple threads executes concurrently,
**   a 'critical section' ensures that no other threads within that zone
**   affect with execution.
**
**   Mut-ex is one of the solutions that can make critical section.
*/

t_bool	sync_init(t_sync *sync)
{
	if (0 != pthread_mutex_init(&sync->mutex, NULL))
		return (raise_error("Failed to init a mutex."));
	return (TRUE);
}

void	sync_uninit(t_sync *sync)
{
	pthread_mutex_destroy(&sync->mutex);
}

void	sync_lock(t_sync *sync)
{
	pthread_mutex_lock(&sync->mutex);
}

void	sync_unlock(t_sync *sync)
{
	pthread_mutex_unlock(&sync->mutex);
}
