/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:36:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 22:42:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_starved(t_philo *philo, t_context *ctx, const time_t time)
{
	return (philo->last_meal + ctx->info->time_to_die < time);
}

void	philo_update_survive(t_philo *philo, t_context *ctx, const time_t time)
{
	if (is_starved(philo, ctx, time))
	{
		philo_drop_the_forks(philo);
		philo_change_state(philo, kDead, time);
	}
	else if (monitor_get_state(ctx->monitor) == kInterrupted)
	{
		philo_drop_the_forks(philo);
		philo->state = kDead;
	}
}
