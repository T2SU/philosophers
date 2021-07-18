/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_semaphore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:20:28 by smun              #+#    #+#             */
/*   Updated: 2021/07/18 19:05:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>

static void	assign_sync_info(t_sync *sync, const t_info *info, int sync_type)
{
	if (sync_type == kMonitor)
	{
		sync->name = SEM_NAME_MONITOR;
		sync->init_num = 1;
	}
	else if (sync_type == kPrinter)
	{
		sync->name = SEM_NAME_PRINT;
		sync->init_num = 1;
	}
	else if (sync_type == kPhilosopher)
	{
		sync->name = SEM_NAME_PHILO;
		sync->init_num = info->numbers;
	}
	else
	{
		sync->name = NULL;
		sync->init_num = -1;
	}
}

t_bool	sync_init(t_sync *sync, const t_info *info, int sync_type)
{
	assign_sync_info(&sync[0], info, sync_type);
	if (sync[0].init_num <= 0 || sync[0].name == NULL)
		return (FALSE);
	sem_unlink(sync[0].name);
	sync[0].sem = sem_open(sync[0].name, O_CREAT, 0644, sync[0].init_num);
	if (sync[0].sem == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}

void	sync_uninit(t_sync *sync, int option)
{
	if ((option & kClose))
		if (sync->sem != SEM_FAILED)
			sem_close(sync->sem);
	if ((option & kDestroy))
		if (sync->name != NULL)
			sem_unlink(sync->name);
}

void	sync_lock(t_sync *sync)
{
	sem_wait(sync->sem);
}

void	sync_unlock(t_sync *sync)
{
	sem_post(sync->sem);
}
