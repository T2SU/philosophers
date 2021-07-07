/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:41 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 15:25:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
** Same code with mandatory part.
*/

static void	philo_change_state(t_philo *philo, int state, time_t time)
{
	philo->state = state;
	print_state(philo->unique_id, state, time);
}

/*
** Changed from mandatory part:
**   :: Mandatory part ::
**       I used 'pthread_mutex_lock' for critical section.
**       it was called in 'fork_try_to_take' function.
**
**   :: Bonus part (this section) ::
**       I use 'sem_wait' for critical section.
**       it was called in 'philo_try_to_take_fork' function.
*/

static void	philo_try_to_eat(t_philo *philo, time_t time)
{
	philo_try_to_take_fork(philo);
	print_fork(philo->unique_id, time);
	philo_try_to_take_fork(philo);
	print_fork(philo->unique_id, time);
	philo->state_end_time = time + philo->info->time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

/*
** Changed from mandatory part:
**   :: Mandatory part ::
**       I used 'pthread_mutex_unlock' for critical section.
**       it was called in 'fork_put_down' function.
**
**   :: Bonus part (this section) ::
**       I use 'sem_post' for critical section.
**       it was called in 'philo_put_down_fork' function.
*/

static void	philo_drop_the_forks(t_philo *philo)
{
	if (philo->state == kEating)
	{
		philo_put_down_fork(philo);
		philo_put_down_fork(philo);
	}
}

/*
** Same code with mandatory part.
*/

static void	philo_stop_to_eat(t_philo *philo, time_t time)
{
	philo_drop_the_forks(philo);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + philo->info->time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

/*
** Same code with mandatory part.
*/

void	philo_update(t_philo *philo)
{
	const time_t	time = time_get();

	if (philo->last_meal + philo->info->time_to_die < time)
	{
		philo_drop_the_forks(philo);
		philo_change_state(philo, kDead, time);
		info_increase_died_count(philo->info);
		return ;
	}
	if (info_get_died_count(philo->info) > 0)
	{
		philo_drop_the_forks(philo);
		philo->state = kDead;
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
