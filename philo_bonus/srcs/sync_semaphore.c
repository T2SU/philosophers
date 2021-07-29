/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_semaphore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:20:28 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 01:54:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>

/*
** ref: https://whatis.techtarget.com/definition/semaphore
**
** Semaphore)
**   Semaphore is also one of the solutions that can make critical section.
**
**   Semaphore can be binary or can have integer value like variable.
*/

static void	assign_sync_info(t_sync *sync, const t_info *info, int sync_type)
{
	if (sync_type == kDiedMonitor)
	{
		sync->name = SEM_NAME_DIED_MONITOR;
		sync->init_num = 0;
	}
	else if (sync_type == kFullMonitor)
	{
		sync->name = SEM_NAME_FULL_MONITOR;
		sync->init_num = 0;
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

/*
**  'sem_open' initialize and open a named semaphore. (BSD man page)
*/

t_bool	sync_init(t_sync *sync, const t_info *info, int sync_type)
{
	assign_sync_info(&sync[0], info, sync_type);
	if (sync[0].init_num < 0 || sync[0].name == NULL)
		return (raise_error("Invalid semaphore info."));
	sem_unlink(sync[0].name);
	sync[0].sem = sem_open(sync[0].name, O_CREAT, 0644, sync[0].init_num);
	if (sync[0].sem == SEM_FAILED)
		return (raise_error("Cannot open a semaphore."));
	return (TRUE);
}

/*
**  'sem_close' will close the semaphore only in current process.
**  It semaphore can be still used in another processes.
**
**  'sem_unlink' will DESTROY(=REMOVE) the named semaphore in the whole system.
**  If that semaphore is in used another process,
**  disassociate it in all using process immediately.
**  Then, it cannot be accessed by all processes.
*/

void	sync_uninit(t_sync *sync, int option)
{
	if ((option & kClose))
		if (sync->sem != SEM_FAILED)
			sem_close(sync->sem);
	if ((option & kDestroy))
		if (sync->name != NULL)
			sem_unlink(sync->name);
}

/*
**  'sem_wait' do decrease semaphore's value. (value--)
**  if semaphore value is already zero,
**  thread will be blocked until it semaphore has positive value.
**
**  'sem_post' do increase semaphore's value. (value++)
**  and if there is a thread that waits by 'sem_wait', resumes it.
*/

void	sync_lock(t_sync *sync)
{
	sem_wait(sync->sem);
}

void	sync_unlock(t_sync *sync)
{
	sem_post(sync->sem);
}
