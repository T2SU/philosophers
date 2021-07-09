/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:29:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/10 01:16:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static int	is_abnormal_exit(int wstatus)
{
	return (wstatus != 0);
}

static void	wait_for_child_process(t_context *ctx, pid_t pid)
{
	int		status;
	int		process_status;

	while (monitor_get_state(ctx->monitor) == kNormal)
	{
		usleep(500);
		process_status = waitpid(pid, &status, WNOHANG);
		if (process_status == 0)
			continue ;
		if (is_abnormal_exit(status))
		{
			monitor_set_state(ctx->monitor, kInterrupted);
			kill(pid, SIGKILL);
		}
		break ;
	}
}

void	*context_run(void *p_ctx)
{
	pid_t		pid;
	t_context	*ctx;
	int			exit_status;

	ctx = (t_context *)p_ctx;
	pid = fork();
	if (pid > 0)
	{
		wait_for_child_process(ctx, pid);
		return (NULL);
	}
	if (pid < 0)
		exit(EXIT_FAILURE);
	context_update(ctx);
	exit_status = monitor_get_state(ctx->monitor) == kInterrupted;
	sync_uninit(&ctx->monitor->sync, kClose);
	sync_uninit(&ctx->printer->sync, kClose);
	sync_uninit(&ctx->philo->fork[0], kClose);
	exit(exit_status);
	return (NULL);
}
