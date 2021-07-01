/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:10:59 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 22:39:08 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static void	*thread_run(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (philo->state != kDead)
	{
		philo_update(philo);
		if (philo->info.number_to_eat > 0)
			if (philo->numbers_had_meal >= philo->info.number_to_eat)
				break ;
		usleep(1);
	}
	return (NULL);
}

void	thread_run_and_join(t_philo *philos, int numbers)
{
	int	i;

	i = 0;
	while (i < numbers)
	{
		pthread_create(&philos[i].thread, NULL, &thread_run, &philos[i]);
		i++;
	}
	i = 0;
	while (i < numbers)
		pthread_join(philos[i++].thread, NULL);
}
