/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:18:14 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 19:24:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Change philosopher's state.
*/

void	philo_change_state(t_philo *philo, int state, time_t time)
{
	printer_changed_state(philo->unique_id, philo->state = state, time);
}

static void	philo_try_to_eat(t_philo *philo, time_t time, int time_to_eat)
{
	if (!philo_forks_try_take(philo))
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
		sync_lock(&philo->fork[0]->sync);
		sync_lock(&philo->fork[1]->sync);
		philo->fork[0]->using = FALSE;
		philo->fork[1]->using = FALSE;
		sync_unlock(&philo->fork[0]->sync);
		sync_unlock(&philo->fork[1]->sync);
	}
}

static void	philo_finish_eating(t_philo *philo, time_t time, int time_to_sleep)
{
	philo_drop_the_forks(philo);
	(philo->numbers_had_meal)++;
	philo->state_end_time = time + time_to_sleep;
	philo_change_state(philo, kSleeping, time);
}

/*
** Update state.
**  When a number of philosophers and forks is odd,
**  Give some delay if state is 'Thinking'.
**  This prevents the philosopher from eating again
**  after he has finished eating.
*/

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
