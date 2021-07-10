/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:20:28 by smun              #+#    #+#             */
/*   Updated: 2021/07/10 18:26:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static void	assign_sync_info(t_sync *sync, const t_info *info, int sync_type)
{
	if (sync_type == kMonitor)
		sync->mutex_num = 1;
	else if (sync_type == kPrinter)
		sync->mutex_num = 1;
	else if (sync_type == kPhilosopher)
		sync->mutex_num = info->numbers;
	else
		sync->mutex_num = -1;
}

t_bool	sync_init(t_sync *sync, const t_info *info, int sync_type)
{
	int	i;

	assign_sync_info(sync, info, sync_type);
	if (sync->mutex_num <= 0)
		return (FALSE);
	i = -1;
	while (++i < sync->mutex_num)
		if (0 != pthread_mutex_init(&sync[i].mutex, NULL))
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
