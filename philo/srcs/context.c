/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:26:31 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:33:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static void	update_if_reached_goal(t_context *ctx)
{
	t_philo		*philo;

	philo = ctx->philo;
	if (!ctx->info->specified_number_to_eat || philo->reached_meal_num)
		return ;
	if (philo->numbers_had_meal < ctx->info->number_to_eat)
		return ;
	philo->reached_meal_num = TRUE;
	if (!monitor_inc_and_check_reached(ctx->died_monitor, ctx->info->numbers))
		return ;
	monitor_set_state(ctx->died_monitor, kInterrupted);
}

/*
** First, Update philosopher's life.
**  If philosopher is on starved, set his state to died. (philo_update_survive)
**
** Then, Update philosopher's state.
**  Process logics by his each state.
**
** Finally, Check philosopher's meal times.
*/

void	context_update(t_context *ctx)
{
	t_philo	*philo;
	time_t	time;

	philo = ctx->philo;
	while (TRUE)
	{
		time = time_get();
		philo_update_survive(philo, ctx, time);
		if (philo->state == kDead)
			break ;
		philo_update_state(philo, ctx, time);
		update_if_reached_goal(ctx);
		usleep(250);
	}
}

static void	*context_run(void *p_ctx)
{
	t_context	*ctx;

	ctx = (t_context *)p_ctx;
	context_update(ctx);
	if (ctx->philo->state == kDead)
		monitor_set_state(ctx->died_monitor, kInterrupted);
	return (NULL);
}

/*
**    ref: https://en.wikipedia.org/wiki/Thread_(computing)
**  Thread is the smallest execution unit which is managed by scheduler in OS.
**  The multiple threads of a given process may be executed concurrently.
**  We use 'pthread_create' system function to create new thread.
*/

void	context_begin(t_simulator *sim)
{
	int			i;
	t_context	*ctx;

	i = 0;
	while (i < sim->info.numbers)
	{
		ctx = &sim->contexts[i];
		ctx->info = &sim->info;
		ctx->died_monitor = &sim->died_monitor;
		ctx->printer = &sim->printer;
		ctx->philo = &sim->philos[i];
		pthread_create(&ctx->thread, NULL, &context_run, ctx);
		i++;
	}
}

/*
** We use 'pthread_join' system function to finish the thread gracefully.
** It will clean up its thread context space. or else it may cause some leaks.
**
** It can be replaced by 'pthread_deatch' if it's not necessary to wait to end,
** for cleaning up thread context.
*/

void	context_wait_to_end(t_simulator *sim)
{
	int		i;

	i = 0;
	while (i < sim->info.numbers)
	{
		pthread_join(sim->contexts[i].thread, NULL);
		i++;
	}
}
