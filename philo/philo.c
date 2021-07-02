/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:41 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 12:45:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	philo_init(int unique_id, t_philo *philo, t_info *info)
{
	ft_bzero(philo, sizeof(t_philo));
	philo->state = kThinking;
	philo->unique_id = unique_id;
	philo->last_meal = time_get();
	philo->state_end_time = time_get();
	philo->info = info;
}

t_bool	philo_change_state(t_philo *philo, int state, const time_t time)
{
	static pthread_mutex_t	mutex;

	if (philo == NULL)
	{
		if (0 != pthread_mutex_init(&mutex, NULL))
			return (FALSE);
		return (TRUE);
	}
	philo->state = state;
	pthread_mutex_lock(&mutex);
	if (state == kEating)
		printf("%ld %d is eating\n", time, philo->unique_id);
	else if (state == kSleeping)
		printf("%ld %d is sleeping\n", time, philo->unique_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, philo->unique_id);
	else if (state == kDead)
		printf("%ld %d is died\n", time, philo->unique_id);
	pthread_mutex_unlock(&mutex);
	return (TRUE);
}

/*
** Trying to pick bigger unique_id of fork.
*/

static void	philo_try_to_eat(t_philo *philo, const time_t time)
{
	if (!fork_try_takes(philo->forks_to_pick))
		return ;
	philo->state_end_time = time + philo->info->time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

static void	philo_stop_to_eat(t_philo *philo, const time_t time)
{
	fork_put_downs(philo->forks_to_pick);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + philo->info->time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

void	philo_update(t_philo *philo)
{
	const time_t	time = time_get();

	if (philo->last_meal + philo->info->time_to_die < time)
	{
		philo_change_state(philo, kDead, time);
		info_increase_died_count(philo->info);
		return ;
	}
	if (philo->state_end_time > time)
		return ;
	if (philo->state == kEating)
		philo_stop_to_eat(philo, time);
	else if (philo->state == kSleeping)
		philo_change_state(philo, kThinking, time);
	else if (philo->state == kThinking)
		philo_try_to_eat(philo, time);
}
