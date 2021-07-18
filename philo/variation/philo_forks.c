/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:29:40 by smun              #+#    #+#             */
/*   Updated: 2021/07/18 19:23:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	try_take(t_philo *philo)
{
	if (philo->fork[0]->using || philo->fork[1]->using)
		return (FALSE);
	if (philo->taken > philo->fork[0]->counter / 2)
		return (FALSE);
	if (philo->taken > philo->fork[1]->counter / 2)
		return (FALSE);
	(philo->taken)++;
	(philo->fork[0]->counter)++;
	(philo->fork[1]->counter)++;
	(philo->fork[0]->using) = TRUE;
	(philo->fork[1]->using) = TRUE;
	return (TRUE);
}

t_bool	philo_forks_try_take(t_philo *philo)
{
	t_bool	success;

	sync_lock(&philo->fork[0]->sync);
	sync_lock(&philo->fork[1]->sync);
	success = try_take(philo);
	sync_unlock(&philo->fork[0]->sync);
	sync_unlock(&philo->fork[1]->sync);
	return (success);
}

void	philo_forks_put_down(t_philo *philo)
{
	sync_lock(&philo->fork[0]->sync);
	sync_lock(&philo->fork[1]->sync);
	philo->fork[0]->using = FALSE;
	philo->fork[1]->using = FALSE;
	sync_unlock(&philo->fork[0]->sync);
	sync_unlock(&philo->fork[1]->sync);
}
