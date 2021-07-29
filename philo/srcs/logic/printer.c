/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:50:54 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 21:26:20 by smun             ###   ########.fr       */
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

void	printer_changed_state(t_philo *philo, int state, const time_t time)
{
	t_printer	*printer;

	printer = *get_printer();
	sync_lock(&printer->sync);
	if (state == kSleeping)
		printf("%ld %d is sleeping\n", time, philo->unique_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, philo->unique_id);
	if (DEBUG)
	{
		if (state == kEating)
			printf("%ld %d is eating (%d)\n", time, philo->unique_id,
				philo->numbers_took_forks);
		else if (state == kDead)
			printf("%ld %d died (%d)\n", time, philo->unique_id,
				philo->numbers_took_forks);
	}
	else
	{
		if (state == kEating)
			printf("%ld %d is eating\n", time, philo->unique_id);
		else if (state == kDead)
			printf("%ld %d died\n", time, philo->unique_id);
	}
	sync_unlock(&printer->sync);
}

void	printer_taken_fork(t_philo *philo, int fork_id, const time_t time)
{
	t_printer	*printer;
	int			picked;

	printer = *get_printer();
	sync_lock(&printer->sync);
	if (DEBUG)
	{
		sync_lock(&philo->fork[fork_id]->sync);
		picked = philo->fork[fork_id]->picked;
		printf("%ld %d has taken a fork %d (%d)\n", time, philo->unique_id,
			philo->fork[fork_id]->unique_id, picked);
		sync_unlock(&philo->fork[fork_id]->sync);
	}
	else
	{
		printf("%ld %d has taken a fork\n", time, philo->unique_id);
	}
	sync_unlock(&printer->sync);
}
