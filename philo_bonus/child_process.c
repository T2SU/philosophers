/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:29:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 00:01:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	*child_run(void *p_child)
{
	int		status;
	pid_t	pid;
	t_child	*child;

	child = (t_child *)p_child;
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (status == EXIT_FAILURE)
			monitor_set_state(child->monitor, kInterrupted);
		return (NULL);
	}
	if (pid < 0)
		exit(EXIT_FAILURE);
	child_update(child);
	sync_uninit(&child->monitor->sync, kClose);
	sync_uninit(&child->printer->sync, kClose);
	sync_uninit(&child->philo->fork[0], kClose);
	return (NULL);
}
