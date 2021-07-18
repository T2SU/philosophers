/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:18:14 by smun              #+#    #+#             */
/*   Updated: 2021/07/18 19:04:56 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_change_state(t_philo *philo, int state, time_t time)
{
	philo->state = state;
	printer_changed_state(philo->unique_id, state, time);
}

static void	philo_try_to_eat(t_philo *philo, time_t time, int time_to_eat)
{
	sync_lock(philo->table);
	printer_taken_fork(philo->unique_id, time);
	sync_lock(philo->table);
	printer_taken_fork(philo->unique_id, time);
	philo->state_end_time = time + time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

void	philo_drop_the_forks(t_philo *philo)
{
	if (philo->state == kEating)
	{
		sync_unlock(philo->table);
		sync_unlock(philo->table);
	}
}

static void	philo_finish_eating(t_philo *philo, time_t time, int time_to_sleep)
{
	philo_drop_the_forks(philo);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

void	philo_update_state(t_philo *philo, t_context *ctx, const time_t time)
{
	if (philo->state_end_time > time)
		return ;
	if (philo->state == kThinking)
		philo_try_to_eat(philo, time, ctx->info->time_to_eat);
	else if (philo->state == kEating)
		philo_finish_eating(philo, time, ctx->info->time_to_sleep);
	else if (philo->state == kSleeping)
		philo_change_state(philo, kThinking, time);
}
