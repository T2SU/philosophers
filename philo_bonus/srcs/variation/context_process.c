/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:29:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 18:41:24 by smun             ###   ########.fr       */
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
		usleep(1000);
		process_status = waitpid(pid, &status, WNOHANG);
		if (process_status == 0)
			continue ;
		if (is_abnormal_exit(status))
			monitor_set_state(ctx->monitor, kInterrupted);
		break ;
	}
	if (monitor_get_state(ctx->monitor) == kInterrupted)
		kill(pid, SIGKILL);
}

static t_bool	context_update(t_context *ctx)
{
	t_philo	*philo;
	time_t	time;

	philo = ctx->philo;
	while (TRUE)
	{
		time = time_get();
		philo_update_survive(philo, ctx, time);
		if (philo->state == kDead)
			return (FALSE);
		philo_update_state(philo, ctx, time);
		if (ctx->info->specified_number_to_eat)
			if (philo->numbers_had_meal >= ctx->info->number_to_eat)
				break ;
		usleep(100);
	}
	return (TRUE);
}

void	*context_run(void *p_ctx)
{
	pid_t		pid;
	t_context	*ctx;
	t_bool		success;

	ctx = (t_context *)p_ctx;
	pid = fork();
	if (pid > 0)
	{
		wait_for_child_process(ctx, pid);
		return (NULL);
	}
	if (pid < 0)
		exit(EXIT_FAILURE);
	success = context_update(ctx);
	sync_uninit(&ctx->monitor->sync, kClose);
	sync_uninit(&ctx->printer->sync, kClose);
	sync_uninit(ctx->table, kClose);
	if (success)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	return (NULL);
}
