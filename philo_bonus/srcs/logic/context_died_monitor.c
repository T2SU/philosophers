/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_died_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 01:58:25 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:52:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>

static void	kill_all_childs(t_simulator *sim)
{
	int	i;

	i = 0;
	while (i < sim->info.numbers)
		kill(sim->contexts[i++].pid, SIGTERM);
}

static void	unwait_full_monitor(t_simulator *sim)
{
	int	i;

	if (!sim->info.specified_number_to_eat)
		return ;
	i = -1;
	while (++i < sim->info.numbers)
		monitor_notify(&sim->full_monitor);
}

static void	*died_monitor_run(void *p_sim)
{
	t_simulator	*sim;

	sim = (t_simulator *)p_sim;
	monitor_wait(&sim->died_monitor);
	kill_all_childs(sim);
	unwait_full_monitor(sim);
	return (NULL);
}

void	context_start_died_monitor(t_simulator *sim)
{
	pthread_create(&sim->died_monitor_thread, NULL, &died_monitor_run, sim);
}
