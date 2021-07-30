/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:29:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:34:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static void	notify_full_if_possible(t_context *ctx)
{
	t_philo	*philo;

	philo = ctx->philo;
	if (!ctx->info->specified_number_to_eat)
		return ;
	if (ctx->notified_full)
		return ;
	if (philo->numbers_had_meal < ctx->info->number_to_eat)
		return ;
	ctx->notified_full = TRUE;
	monitor_notify(ctx->full_monitor);
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
		notify_full_if_possible(ctx);
		usleep(250);
	}
	return (TRUE);
}

void	*context_run(void *p_ctx)
{
	pid_t		pid;
	t_context	*ctx;
	int			status;

	ctx = (t_context *)p_ctx;
	pid = fork();
	if (pid > 0)
	{
		waitpid(ctx->pid = pid, &status, 0);
		return (NULL);
	}
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (!context_update(ctx))
		monitor_notify(ctx->died_monitor);
	sync_uninit(&ctx->died_monitor->sync, kClose);
	sync_uninit(&ctx->full_monitor->sync, kClose);
	sync_uninit(&ctx->printer->sync, kClose);
	sync_uninit(ctx->table, kClose);
	return (NULL);
}
