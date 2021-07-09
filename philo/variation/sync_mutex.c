/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:20:28 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 21:23:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	sync_init(t_sync *sync, const t_info *info, int sync_type)
{
	(void)info;
	(void)sync_type;
	if (0 != pthread_mutex_init(&sync->mutex, NULL))
		return (FALSE);
	return (TRUE);
}

void	sync_uninit(t_sync *sync, int option)
{
	if ((option & kDestroy))
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
