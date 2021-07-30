/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:50:34 by smun              #+#    #+#             */
/*   Updated: 2021/07/30 01:53:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>

static t_bool	parse_details(t_info *info, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (raise_error("./philo <numbers> <time_to_die> <time_to_eat> "
				"<time_to_sleep> (<number_to_eat>)"));
	info->specified_number_to_eat = (argc == 6);
	if (argc == 6 && !ft_atoi_strict(argv[5], &info->number_to_eat))
		return (raise_error("Failed to parsing 'number_to_eat'"));
	if (!ft_atoi_strict(argv[4], &info->time_to_sleep))
		return (raise_error("Failed to parsing 'time_to_sleep'"));
	if (!ft_atoi_strict(argv[3], &info->time_to_eat))
		return (raise_error("Failed to parsing 'time_to_eat'"));
	if (!ft_atoi_strict(argv[2], &info->time_to_die))
		return (raise_error("Failed to parsing 'time_to_die'"));
	if (!ft_atoi_strict(argv[1], &info->numbers))
		return (raise_error("Failed to parsing 'numbers'"));
	if (info->specified_number_to_eat && info->number_to_eat <= 0)
		return (raise_error("'number_to_eat' must be positive number."));
	if (info->time_to_sleep <= 0)
		return (raise_error("'time_to_sleep' must be positive number."));
	if (info->time_to_eat <= 0)
		return (raise_error("'time_to_eat' must be positive number."));
	if (info->time_to_die <= 0)
		return (raise_error("'time_to_die' must be positive number."));
	if (info->numbers <= 0)
		return (raise_error("Numbers must be positive number."));
	return (TRUE);
}

/*
** ref: https://en.wikipedia.org/wiki/Dining_philosophers_problem
**
** Sync types:
**   1. Monitor
**   2. Printer
**   3. Fork
**
** - Monitor synchronization
**     Guard the setting/getting the simulator state.
**     when simulator has interrupted state, the simulation will be end.
**
** - Printer synchronization
**     Guard the print to stdout for no scrambled or intertwined.
**
** - Fork synchronization
**     Guard the using state or picked count of each forks.
*/

/*
** - Asymmetric solutions.
**    (https://osf.io/kbyhq)
**
** Using asymmetric solutions, namely philosophers in odd numbers
** took a left chopstick first and right chopsticks.
**
** While sitting on a chair philosopher
** even take the right chopstick first, and chopsticks left.
*/

static t_bool	init_sync(t_simulator *sim)
{
	const t_info	*info = &sim->info;
	int				i;

	if (!sync_init(&sim->died_monitor.sync))
		return (raise_error("Failed to init 'Monitor' sync"));
	if (!sync_init(&sim->printer.sync))
		return (raise_error("Failed to init 'Printer' sync"));
	i = -1;
	while (++i < info->numbers)
	{
		if (!sync_init(&sim->forks[i].sync))
			return (raise_error("Failed to init 'Philosopher' sync"));
		if ((i & 1) == 0)
		{
			sim->philos[i].fork[0] = &sim->forks[(i + 0) % info->numbers];
			sim->philos[i].fork[1] = &sim->forks[(i + 1) % info->numbers];
		}
		else
		{
			sim->philos[i].fork[1] = &sim->forks[(i + 0) % info->numbers];
			sim->philos[i].fork[0] = &sim->forks[(i + 1) % info->numbers];
		}
	}
	return (TRUE);
}

static t_bool	init_logic_objects(t_simulator *sim)
{
	const time_t	time = time_get();
	const t_info	*info = &sim->info;
	int				i;
	t_philo			*philo;

	sim->philos = malloc(sizeof(t_philo) * info->numbers);
	sim->forks = malloc(sizeof(t_fork) * info->numbers);
	sim->contexts = malloc(sizeof(t_context) * info->numbers);
	if (sim->philos == NULL || sim->forks == NULL || sim->contexts == NULL)
		return (raise_error("Out of memory"));
	i = -1;
	while (++i < info->numbers)
	{
		philo = &sim->philos[i];
		memset(philo, 0, sizeof(t_philo));
		philo->state = kThinking;
		philo->unique_id = i + 1;
		philo->last_meal = time;
		philo->state_end_time = time;
		memset(&sim->forks[i], 0, sizeof(t_fork));
		sim->forks[i].unique_id = i + 1;
	}
	return (TRUE);
}

t_bool	simulator_init(t_simulator *sim, int argc, char *argv[])
{
	memset(sim, 0, sizeof(t_simulator));
	if (!parse_details(&sim->info, argc, argv))
		return (FALSE);
	if (!init_logic_objects(sim))
		return (FALSE);
	if (!init_sync(sim))
		return (FALSE);
	printer_set(&sim->printer);
	time_get();
	return (TRUE);
}

int	simulator_uninit(t_simulator *sim, int exit_code)
{
	int	i;

	if (sim->philos != NULL)
	{
		i = -1;
		while (++i < sim->info.numbers)
			sim->philos[i].state = kDead;
	}
	sync_uninit(&sim->died_monitor.sync);
	sync_uninit(&sim->printer.sync);
	if (sim->forks != NULL)
	{
		i = -1;
		while (++i < sim->info.numbers)
			sync_uninit(&sim->forks[i].sync);
	}
	free(sim->philos);
	free(sim->forks);
	free(sim->contexts);
	return (exit_code);
}
