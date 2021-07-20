/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:29:40 by smun              #+#    #+#             */
/*   Updated: 2021/07/20 19:32:46 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Distribution forks by referenced counter. (Arbitrator solution)
** This ensures that the philosophers next to each fork take turns picking up.
**   - Pickable = PhilosopherCounter <= ForkCounter / 2
**
**          [Fork-5]  [Philosopher-1]  [Fork-1]  [Philosohper-2]  [Fork-2] ...
**    Init     0             0             0            0             0
**   ------------------------------------------------------------------------
**     >> All Philosohpers can pick forks.
**
** Round-1     1             1             1            0             0
**   ------------------------------------------------------------------------
**	   - Philo-1: forks[0] = Fork-5, forks[1] = Fork-1
**     >>  Fork-5:(Fork-5 Counter / 2 >= Philo-1 Counter?)
**     >>          = (0 / 2 >= 0)
**     >>          = TRUE
**     >>  Fork-1:(Fork-1 Counter / 2 >= Philo-1 Counter?)
**     >>          = (0 / 2 >= 0)
**     >>          = TRUE
**     >> [O] Philo-1 can pick up Fork-5 and Fork-1.
**
** Round-2     1             1             1            0             0
**   ------------------------------------------------------------------------
**     - Philo-1: forks[0] = Fork-5, forks[1] = Fork-1
**     >>  Fork-5:(Fork-5 Counter / 2 >= Philo-1 Counter?)
**     >>          = (1 / 2 >= 1)
**     >>          = FALSE
**     >>  Fork-1:(Fork-1 Counter / 2 >= Philo-1 Counter?)
**     >>          = (1 / 2 >= 1)
**     >>          = FALSE
**     >> [X] Philo-1 cannot pick up Fork-5 and Fork-1
**     - Philo-2: forks[0] = Fork-1,  forks[1] = Fork-2
**     >>  Fork-1:(Fork-1 Counter / 2 >= Philo-2 Counter?)
**     >>          = (1 / 2 >= 0)
**     >>          = TRUE
**     >>  Fork-2:(Fork-2 Counter / 2 >= Philo-2 Counter?)
**     >>          = (0 / 2 >= 0)
**     >>          = TRUE
**     >> [O] Philo-2 can pick up Fork-1 and Fork-2
**
** Round-3     1             1             2            1             1
**   ------------------------------------------------------------------------
**     - Philo-1: forks[0] = Fork-5, forks[1] = Fork-1
**     >>  Fork-5:(Fork-5 Counter / 2 >= Philo-1 Counter?)
**     >>          = (1 / 2 >= 1)
**     >>          = FALSE
**     >>  Fork-1:(Fork-1 Counter / 2 >= Philo-1 Counter?)
**     >>          = (2 / 2 >= 1)
**     >>          = TRUE
**     >> [X] Philo-1 cannot pick up Fork-5 and Fork-1
**     - Philo-2: forks[0] = Fork-1,  forks[1] = Fork-2
**     >>  Fork-1:(Fork-1 Counter / 2 >= Philo-2 Counter?)
**     >>          = (2 / 2 >= 1)
**     >>          = TRUE
**     >>  Fork-2:(Fork-2 Counter / 2 >= Philo-2 Counter?)
**     >>          = (1 / 2 >= 1)
**     >>          = FALSE
**     >> [O] Philo-2 cannot pick up Fork-1 and Fork-2
**     ...
*/

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

	if (philo->fork[0] == philo->fork[1])
		return (FALSE);
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
