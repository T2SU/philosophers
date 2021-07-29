/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:18:14 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:25:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_change_state(t_philo *philo, int state, time_t time)
{
	printer_changed_state(philo, philo->state = state, time);
}

static void	philo_try_to_eat(t_philo *philo, t_context *ctx, int time_to_eat)
{
	time_t	time;

	if (philo->forks_num <= 1)
		return ;
	if (philo->last_meal == 0 && (philo->unique_id & 1))
		if (time_get() < time_to_eat)
			return ;
	sync_lock(philo->table);
	sync_lock(philo->table);
	time = time_get();
	if (is_starved(philo, ctx, time))
		return ;
	printer_taken_fork(philo->unique_id, time);
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
		philo_try_to_eat(philo, ctx, ctx->info->time_to_eat);
	else if (philo->state == kEating)
		philo_finish_eating(philo, time, ctx->info->time_to_sleep);
	else if (philo->state == kSleeping)
		philo_change_state(philo, kThinking, time);
}
