/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:26:31 by smun              #+#    #+#             */
/*   Updated: 2021/07/08 23:55:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <unistd.h>

void	child_update(t_child *child)
{
	t_philo	*philo;

	philo = child->philo;
	while (philo->state != kDead)
	{
		philo_update(philo, child);
		if (child->info->specified_number_to_eat)
			if (philo->numbers_had_meal >= child->info->number_to_eat)
				break ;
		usleep(250);
	}
}

void	child_begin(t_simulator *sim)
{
	int		i;
	t_child	*child;
	
	i = 0;
	while (i < sim->info.numbers)
	{
		child = &sim->childs[i];
		child->info = &sim->info;
		child->monitor = &sim->monitor;
		child->printer = &sim->printer;
		child->philo = &sim->philos[i];
		pthread_create(&child->thread, NULL, &child_run, child);
		i++;
	}
}

void	child_wait_to_end(t_simulator *sim)
{
	int		i;
	
	i = 0;
	while (i < sim->info.numbers)
	{
		pthread_join(sim->childs[i].thread, NULL);
		i++;
	}
}
