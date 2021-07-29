/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:26:31 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 18:39:53 by smun             ###   ########.fr       */
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
		ctx->monitor = &sim->monitor;
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
}
