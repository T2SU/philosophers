/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:50:54 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 02:24:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
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

void	printer_changed_state(t_philo *philo, int state, const time_t time)
{
	t_printer	*printer;

	printer = *get_printer();
	sync_lock(&printer->sync);
	if (state == kSleeping && DEBUG)
		printf("%ld %d is sleeping (had_meal:%d)\n", time, philo->unique_id,
			philo->numbers_had_meal);
	else if (state == kSleeping && !DEBUG)
		printf("%ld %d is sleeping\n", time, philo->unique_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, philo->unique_id);
	else if (state == kEating)
		printf("%ld %d is eating\n", time, philo->unique_id);
	else if (state == kDead && DEBUG)
		printf("%ld %d died (had_meal:%d)\n", time, philo->unique_id,
			philo->numbers_had_meal);
	else if (state == kDead && !DEBUG)
		printf("%ld %d died\n", time, philo->unique_id);
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
