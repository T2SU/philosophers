/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:29 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 15:26:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

/*
** Try to take a fork.
*/

void	philo_try_to_take_fork(t_philo *philo)
{
	sem_wait(philo->info->semaphore);
}

/*
** Put down a fork.
*/

void	philo_put_down_fork(t_philo *philo)
{
	sem_post(philo->info->semaphore);
}
