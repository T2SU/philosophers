/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_full_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 01:59:10 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:13:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>

static void	*full_monitor_run(void *p_sim)
{
	t_simulator	*sim;
	int		i;

	sim = (t_simulator *)p_sim;
	i = 0;
	while (i < sim->info.numbers)
	{
		monitor_wait(&sim->full_monitor);
		i++;
	}
	i = 0;
	while (i < sim->info.numbers)
		kill(sim->contexts[i++].pid, SIGTERM);
	return (NULL);
}

void	context_start_full_monitor(t_simulator *sim)
{
	if (!sim->info.specified_number_to_eat)
		return ;
	pthread_create(&sim->full_monitor_thread, NULL, &full_monitor_run, sim);
}
