/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:16:09 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 01:53:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_wait(t_monitor *mon)
{
	sync_lock(&mon->sync);
}

void	monitor_notify(t_monitor *mon)
{
	sync_unlock(&mon->sync);
}
