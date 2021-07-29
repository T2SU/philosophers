/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:16:09 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:33:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_get_state(t_monitor *mon)
{
	int	ret;

	sync_lock(&mon->sync);
	ret = mon->state;
	sync_unlock(&mon->sync);
	return (ret);
}

void	monitor_set_state(t_monitor *mon, int state)
{
	sync_lock(&mon->sync);
	mon->state = state;
	sync_unlock(&mon->sync);
}

t_bool	monitor_inc_and_check_reached(t_monitor *mon, int goal)
{
	t_bool	ret;

	sync_lock(&mon->sync);
	ret = goal == ++(mon->reached_philos);
	sync_unlock(&mon->sync);
	return (ret);
}
