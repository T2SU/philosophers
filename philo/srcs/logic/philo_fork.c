/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 04:08:21 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 16:24:46 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** << Step 1 >>
**
**  First, an even number of philosophers take their forks.
**   ('check_preemptive_from_beginning' function)
**
** +-------+---+---+---+---+---+
** |       | 1 | 2 | 3 | 4 | 5 |
** +-------+---+---+---+---+---+
** | Philo | 0 | 0 | 0 | 0 | 0 |
** +-------+---+---+---+---+---+
** |  Fork | 0 | 0 | 0 | 0 | 0 |
** +-------+---+---+---+---+---+
** |   Run | X | O | X | O | X |
** +-------+---+---+---+---+---+
**
**  << Step 2 >>
**
**  Using the 'picked' value of the fork and
**  'numbers_took_forks' value of the philosopher,
**  compare the preemption between the opponent and his own philosopher.
**
**  If the calculated value of the opponent's 'numbers_took_forks' value is
**  lower than its own philosopher's 'numbers_took_forks' value,
**  It yields to the opponent philosopher to pick up the fork.
**
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |       | 1 | 2 | 3 | 4 | 5 |   |       | 1 | 2 | 3 | 4 | 5 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** | Philo | 0 | 1 | 0 | 1 | 0 |   | Philo | 0 | 1 | 0 | 1 | 0 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |  Fork | 1 | 1 | 1 | 1 | 0 |   |  Fork | 1 | 1 | 1 | 1 | 0 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |   Run | X | S | O | S | O |   |   Run | O | S | O | S | X |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
**
**  << Step 3 >>
**
**  Afterwards,
**  the fork is provided by checking whether it is still possible to preempt.
**
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |       | 1 | 2 | 3 | 4 | 5 |   |       | 1 | 2 | 3 | 4 | 5 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** | Philo | 0 | 1 | 1 | 1 | 1 |   | Philo | 1 | 1 | 1 | 1 | 0 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |  Fork | 1 | 2 | 2 | 2 | 1 |   |  Fork | 2 | 2 | 2 | 1 | 1 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |   Run | O | X | S | O | S |   |   Run | S | O | S | X | O |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
**
**  << Step 4 >>
**
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |       | 1 | 2 | 3 | 4 | 5 |   |       | 1 | 2 | 3 | 4 | 5 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** | Philo | 1 | 1 | 1 | 2 | 1 |   | Philo | 1 | 2 | 1 | 1 | 1 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |  Fork | 2 | 2 | 3 | 3 | 2 |   |  Fork | 3 | 3 | 2 | 2 | 2 |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
** |   Run | S | O | X | S | O |   |   Run | O | S | X | O | S |
** +-------+---+---+---+---+---+   +-------+---+---+---+---+---+
*/

/*
** Check if this philosohper is preemptive than the other one.
**
**   'Picked' - 'Taken' = Other philosopher's numbers_took_forks count.
**
**     other_philo.numbers_took_forks = fork.picked - philo.numbers_took_forks
**     if (other_philo.numbers_took_forks >= philo.numbers_took_forks)
**         is_preemptive = TRUE;
**
**      other_philo.numbers_took_forks >= philo.numbers_took_forks
**  ->  fork.picked - philo.numbers_took_forks >= philo.numbers_took_forks
**  ->  fork.picked >= (philo.numbers_took_forks * 2)
**  ->  fork.picked >= (philo.numbers_took_forks << 1)
*/

static t_bool	is_preemptive_than_other(t_philo *philo)
{
	if (philo->fork[0]->picked < (philo->numbers_took_forks << 1))
		return (FALSE);
	if (philo->fork[1]->picked < (philo->numbers_took_forks << 1))
		return (FALSE);
	return (TRUE);
}

/*
** An even number of philosophers are guaranteed to pick the fork first.
** It makes each philosopher to pick the forks sequentially without starvation.
*/

static t_bool	check_preemption_from_beginning(t_philo *philo)
{
	const int	odd = philo->unique_id & 1;

	return (odd == 0);
}

static t_bool	try_take(t_philo *philo)
{
	if (philo->fork[0]->using || philo->fork[1]->using)
		return (FALSE);
	if (philo->fork[0]->picked == 0 && philo->fork[1]->picked == 0)
		if (!check_preemption_from_beginning(philo))
			return (FALSE);
	if (!is_preemptive_than_other(philo))
		return (FALSE);
	(philo->fork[0]->picked)++;
	(philo->fork[1]->picked)++;
	(philo->numbers_took_forks)++;
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
