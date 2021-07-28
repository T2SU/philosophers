/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:50:54 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 00:44:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static t_printer	**get_printer(void)
{
	static t_printer	*printer;

	return (&printer);
}

void	printer_set(t_printer *printer)
{
	*get_printer() = printer;
}

t_bool	check_monitor_state()
{
	t_printer	*printer;
	t_monitor	*monitor;
	t_bool		ret;

	printer = *get_printer();
	monitor = printer->monitor;
	sync_lock(&monitor->sync);
	ret = (monitor->state == kNormal);
	sync_unlock(&monitor->sync);
	return (ret);
}

void	printer_changed_state(int philo_id, int state, const time_t time)
{
	t_printer	*printer;

	printer = *get_printer();
	sync_lock(&printer->sync);
	if (state == kEating)
		printf("%ld %d is eating\n", time, philo_id);
	else if (state == kSleeping)
		printf("%ld %d is sleeping\n", time, philo_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, philo_id);
	else if (state == kDead)
		printf("%ld %d died\n", time, philo_id);
	sync_unlock(&printer->sync);
}

void	printer_taken_fork(int philo_id, const time_t time)
{
	t_printer	*printer;

	printer = *get_printer();
	sync_lock(&printer->sync);
	printf("%ld %d has taken a fork\n", time, philo_id);
	sync_unlock(&printer->sync);
}
