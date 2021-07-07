/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:08:27 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

static sem_t	**get_print_semaphore(void)
{
	static sem_t	*sem;

	return (&sem);
}

t_bool	print_init(void)
{
	sem_t	*sem;

	sem = sem_open(SEM_NAME_PRINT, O_CREAT, 0644);
	if (sem == NULL)
		return (FALSE);
	sem_post(sem);
	*get_print_semaphore() = sem;
	return (TRUE);
}

void	print_close(void)
{
	sem_close(*get_print_semaphore());
}

void	print_state(int unique_id, int state, const time_t time)
{
	sem_t	*sem;

	sem = *get_print_semaphore();
	sem_wait(sem);
	if (state == kEating)
		printf("%ld %d is eating\n", time, unique_id);
	else if (state == kSleeping)
		printf("%ld %d is sleeping\n", time, unique_id);
	else if (state == kThinking)
		printf("%ld %d is thinking\n", time, unique_id);
	else if (state == kDead)
		printf("%ld %d is died\n", time, unique_id);
	sem_post(sem);
}

void	print_fork(int unique_id, const time_t time)
{
	sem_t	*sem;

	sem = *get_print_semaphore();
	sem_wait(sem);
	printf("%ld %d has taken a fork\n", time, unique_id);
	sem_post(sem);
}
