/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:41 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 17:13:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void				philo_init(int unique_id, t_philo *philo, t_info *info)
{
	ft_bzero(philo, sizeof(t_philo));
	philo->state = kThinking;
	philo->unique_id = unique_id;
	philo->last_meal = time_get();
	philo->state_end_time = time_get();
	philo->info = info;
}

void				philo_change_state(t_philo *philo, int state, time_t time)
{
	philo->state = state;
	print_state(philo->unique_id, state, time);
}

/*
** Trying to pick bigger unique_id of fork.
*/

static void			philo_try_to_eat(t_philo *philo, time_t time)
{
	if (fork_is_same(philo->prioritized_forks))
		return ;
	fork_try_to_take(philo->prioritized_forks[0]);
	print_fork(philo->unique_id, time);
	fork_try_to_take(philo->prioritized_forks[1]);
	print_fork(philo->unique_id, time);
	philo->state_end_time = time + philo->info->time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

static void			philo_stop_to_eat(t_philo *philo, time_t time)
{
	fork_put_down(philo->prioritized_forks[0]);
	fork_put_down(philo->prioritized_forks[1]);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + philo->info->time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

void				philo_update(t_philo *philo)
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
