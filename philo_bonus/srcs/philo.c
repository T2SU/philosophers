/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:18:14 by smun              #+#    #+#             */
/*   Updated: 2021/07/31 14:57:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_change_state(t_philo *philo, int state, time_t time)
{
	printer_changed_state(philo, philo->state = state, time);
}

static void	philo_try_to_eat(t_philo *philo, t_context *ctx, int time_to_eat)
{
	int		i;
	time_t	time;

	if (philo->forks_num <= 1)
		return ;
	if (philo->last_meal == 0 && (philo->unique_id & 1))
		if (time_get() < time_to_eat)
			return ;
	i = -1;
	while (++i < 2)
	{
		sync_lock(philo->table);
		philo_update_survive(philo, ctx, time = time_get());
		if (philo->state == kDead)
			return ;
		printer_taken_fork(philo->unique_id, time);
		(philo->picking_forks)++;
	}
	philo->state_end_time = time + time_to_eat;
	philo->last_meal = time;
	philo_change_state(philo, kEating, time);
}

void	philo_drop_the_forks(t_philo *philo)
{
	if (philo->picking_forks <= 0)
		return ;
	if (DEBUG)
		printer_print("       %3d has %d forks\n",
			philo->unique_id, philo->picking_forks);
	while (philo->picking_forks > 0)
	{
		if (DEBUG)
			printer_print("%6ld %3d put down the fork\n",
				time_get(), philo->unique_id);
		sync_unlock(philo->table);
		philo->picking_forks--;
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
