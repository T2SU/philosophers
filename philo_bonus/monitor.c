/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:16:09 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 19:30:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		monitor_get_died_count(t_monitor *mon)
{
	int	ret;

	sync_lock(&mon->sync);
	ret = mon->died_count;
	sync_unlock(&mon->sync);
	return (ret);
}

void	monitor_inc_died_count(t_monitor *mon)
{
	sync_lock(&mon->sync);
	mon->died_count++;
	sync_unlock(&mon->sync);
}
