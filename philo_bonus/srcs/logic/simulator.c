/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:50:34 by smun              #+#    #+#             */
/*   Updated: 2021/07/29 16:21:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>
#include <stdlib.h>

static t_bool	parse_details(t_info *info, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (raise_error("./philo_bonus <numbers> <time_to_die> "
				"<time_to_eat> <time_to_sleep> (<number_to_eat>)"));
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
	if (info->number_to_eat < 0)
		return (raise_error("'number_to_eat' must be positive number."));
	if (info->time_to_sleep < 0)
		return (raise_error("'time_to_sleep' must be positive number."));
	if (info->time_to_eat < 0)
		return (raise_error("'time_to_eat' must be positive number."));
	if (info->time_to_die < 0)
		return (raise_error("'time_to_die' must be positive number."));
	if (info->numbers <= 0)
		return (raise_error("Numbers must be positive number."));
	return (TRUE);
}

static t_bool	init_sync(t_simulator *sim)
{
	const t_info	*info = &sim->info;

	if (!sync_init(&sim->monitor.sync, info, kMonitor))
		return (raise_error("Failed to init 'Monitor' sync"));
	if (!sync_init(&sim->printer.sync, info, kPrinter))
		return (raise_error("Failed to init 'Printer' sync"));
	if (!sync_init(&sim->table, info, kPhilosopher))
		return (raise_error("Failed to init 'Philosopher' sync"));
	return (TRUE);
}

static t_bool	init_logic_objects(t_simulator *sim)
{
	const t_info	*info = &sim->info;
	int				i;
	t_philo			*philo;

	sim->philos = malloc(sizeof(t_philo) * info->numbers);
	sim->contexts = malloc(sizeof(t_context) * info->numbers);
	if (sim->philos == NULL || sim->contexts == NULL)
		return (raise_error("Out of memory"));
	i = -1;
	while (++i < info->numbers)
	{
		philo = &sim->philos[i];
		memset(philo, 0, sizeof(t_philo));
		philo->state = kThinking;
		philo->unique_id = i + 1;
		philo->table = &sim->table;
		philo->forks_num = info->numbers;
		philo->last_meal = time_get();
		philo->state_end_time = time_get();
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
	sync_uninit(&sim->monitor.sync, kClose | kDestroy);
	sync_uninit(&sim->printer.sync, kClose | kDestroy);
	sync_uninit(&sim->table, kClose | kDestroy);
	free(sim->philos);
	free(sim->contexts);
	return (exit_code);
}
