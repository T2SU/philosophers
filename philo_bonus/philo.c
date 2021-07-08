/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:18:14 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 20:53:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_change_state(t_philo *philo, int state, time_t time)
{
	philo->state = state;
	printer_changed_state(philo->unique_id, state, time);
}

static void	philo_try_to_eat(t_philo *philo, time_t time, int time_to_eat)
{
	sync_lock(&philo->fork[0]);
	printer_taken_fork(philo->unique_id, time);
	sync_lock(&philo->fork[1]);
	printer_taken_fork(philo->unique_id, time);
	philo->state_end_time = time + time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

static void	philo_drop_the_forks(t_philo *philo)
{
	if (philo->state == kEating)
	{
		sync_unlock(&philo->fork[0]);
		sync_unlock(&philo->fork[1]);
	}
}

static void	philo_finish_eating(t_philo *philo, time_t time, int time_to_sleep)
{
	philo_drop_the_forks(philo);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

void	philo_update(t_philo *philo, t_child *child)
{
	const time_t	time = time_get();

	if (philo->last_meal + child->info->time_to_die < time)
	{
		philo_drop_the_forks(philo);
		philo_change_state(philo, kDead, time);
		monitor_inc_died_count(child->monitor);
		return ;
	}
	if (monitor_get_died_count(child->monitor) > 0)
	{
		philo_drop_the_forks(philo);
		philo->state = kDead;
		return ;
	}
	if (philo->state_end_time > time)
		return ;
	if (philo->state == kEating)
		philo_finish_eating(philo, time, child->info->time_to_sleep);
	else if (philo->state == kSleeping)
		philo_change_state(philo, kThinking, time);
	else if (philo->state == kThinking)
		philo_try_to_eat(philo, time, child->info->time_to_eat);
}
