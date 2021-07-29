/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:26:31 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:02:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <unistd.h>

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
		ctx->full_monitor = &sim->full_monitor;
		ctx->printer = &sim->printer;
		ctx->philo = &sim->philos[i];
		ctx->table = &sim->table;
		pthread_create(&ctx->thread, NULL, &context_run, ctx);
		i++;
	}
}

void	context_wait_to_end(t_simulator *sim)
{
	int		i;

	i = 0;
	while (i < sim->info.numbers)
	{
		pthread_join(sim->contexts[i].thread, NULL);
		i++;
	}
	monitor_notify(&sim->died_monitor);
	pthread_join(sim->died_monitor_thread, NULL);
	if (!sim->info.specified_number_to_eat)
		return ;
	pthread_join(sim->full_monitor_thread, NULL);
}
