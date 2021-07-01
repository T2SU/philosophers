/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:41 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 19:51:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

t_bool	philo_change_state(t_philo *philo, int state)
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
		printf("%d %d is eating\n", time, philo->unique_id);
	else if (state == kSleeping)
		printf("%d %d is sleeping\n", time, philo->unique_id);
	else if (state == kThinking)
		printf("%d %d is thinking\n", time, philo->unique_id);
	else if (state == kDead)
		printf("%d %d is died\n", time, philo->unique_id);
	pthread_mutex_unlock(&mutex);
	return (TRUE);
}

/*
** Trying to pick bigger unique_id of fork.
*/

static void	philo_try_to_eat(t_philo *philo, const suseconds_t time)
{
	t_fork				*fork;

	fork = philo->pickable_forks[philo->taken_forks];
	if (!fork_try_take(fork))
		return ;
	if (++(philo->taken_forks) < 2)
		return ;
	philo->state_end_time = time + philo->info.time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating);
}

static void	philo_stop_to_eat(t_philo *philo)
{
	philo->taken_forks = 0;
	fork_put_down(philo->pickable_forks[0]);
	fork_put_down(philo->pickable_forks[1]);
}

void	philo_update(t_philo *philo)
{
	const suseconds_t	time = time_get();

	if (philo->last_meal + philo->info.time_to_die < time)
	{
		philo_change_state(philo, kDead);
		return ;
	}
	if (philo->state_end_time > time)
		return ;
	if (philo->state == kEating)
	{
		philo_stop_to_eat(philo);
		(philo->numbers_had_meal)++;
		philo->state_end_time = time + philo->info.time_to_sleep;
		philo_change_state(philo, kSleeping);
	}
	else if (philo->state == kSleeping)
		philo_change_state(philo, kThinking);
	else if (philo->state == kThinking)
		philo_try_to_eat(philo, time);
}
