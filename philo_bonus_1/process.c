/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:10:59 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	simulate_philosopher(t_philo *philo)
{
	while (philo->state != kDead)
	{
		philo_update(philo);
		if (philo->info->specified_number_to_eat)
			if (philo->numbers_had_meal >= philo->info->number_to_eat)
				break ;
		usleep(250);
	}
	semaphore_close(philo->info->semaphore);
	semaphore_close(philo->info->sem_monitor);
	print_close();
}

static void	*process_child_run(void *p_philo)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (NULL);
	}
	if (pid < 0)
		exit(EXIT_FAILURE);
	simulate_philosopher((t_philo *)p_philo);
	return (NULL);
}

void	process_child_begin(pthread_t *threads, t_philo *philos, int n)
{
	int	i;
	
	i = 0;
	while (i < n)
	{
		pthread_create(&threads[i], NULL, &process_child_run, &philos[i]);
		i++;
	}
}

void	process_child_join(pthread_t *threads, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
