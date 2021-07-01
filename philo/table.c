/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:48:30 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 20:03:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

/*
** Set philosopher's pickable and prioritied forks by its unique id.
*/

static void	set_pickable_forks(int numbers, t_philo *philo, t_fork *forks)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = (philo->unique_id + 0) % numbers;
	right_fork_id = (philo->unique_id + 1) % numbers;
	if (forks[left_fork_id].unique_id > forks[right_fork_id].unique_id)
	{
		philo->pickable_forks[0] = &forks[left_fork_id];
		philo->pickable_forks[1] = &forks[right_fork_id];
	}
	else
	{
		philo->pickable_forks[0] = &forks[right_fork_id];
		philo->pickable_forks[1] = &forks[left_fork_id];
	}
}

static void	philo_init(int unique_id, t_philo *philo, t_info info)
{
	ft_bzero(philo, sizeof(t_philo));
	philo->state = kThinking;
	philo->unique_id = unique_id;
	philo->last_meal = time_get();
	philo->state_end_time = time_get();
	philo->info = info;
}

static t_bool	fork_init(int unique_id, t_fork *fork)
{
	if (0 != pthread_mutex_init(&fork->mutex, NULL))
		return (FALSE);
	fork->state = kNotUsing;
	fork->unique_id = unique_id;
	return (TRUE);
}

t_bool	table_init(t_info info, t_fork **forks, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * info.numbers);
	*forks = malloc(sizeof(t_fork) * info.numbers);
	if (*philos == NULL || *forks == NULL)
		return (FALSE);
	if (!philo_change_state(NULL, 0, 0))
		return (FALSE);
	i = 0;
	while (i < info.numbers)
	{
		if (!fork_init(i + 1, &(*forks)[i]))
			return (FALSE);
		philo_init(i + 1, &(*philos)[i], info);
		i++;
	}
	i = 0;
	while (i < info.numbers)
		set_pickable_forks(info.numbers, philos[i++], *forks);
	return (TRUE);
}

void	table_free(t_info info, t_fork **forks, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < info.numbers)
		(*philos)[i++].state = kDead;
	i = 0;
	while (i < info.numbers)
		pthread_mutex_destroy(&(*forks)[i++].mutex);
	free(*forks);
	free(*philos);
}
