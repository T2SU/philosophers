/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:16:09 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 21:18:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		monitor_get_state(t_monitor *mon)
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
