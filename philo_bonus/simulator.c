/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:50:34 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 19:30:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

static t_bool	parse_details(t_info *info, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (FALSE);
	info->specified_number_to_eat = (argc == 6);
	if (argc == 6 && !ft_atoi_strict(argv[5], &info->number_to_eat))
		return (FALSE);
	if (!ft_atoi_strict(argv[4], &info->time_to_sleep))
		return (FALSE);
	if (!ft_atoi_strict(argv[3], &info->time_to_eat))
		return (FALSE);
	if (!ft_atoi_strict(argv[2], &info->time_to_die))
		return (FALSE);
	if (!ft_atoi_strict(argv[1], &info->numbers))
		return (FALSE);
	if (info->numbers < 0)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_sync(t_simulator *sim)
{
	const t_info	*info = &sim->info;
	int				i;

	if (!sync_init(&sim->monitor.sync, info, kMonitor))
		return (FALSE);
	if (!sync_init(&sim->printer.sync, info, kPrinter))
		return (FALSE);
	if (!sync_init(sim->forks, info, kPhilosopher))
		return (FALSE);
	i = -1;
	while (++i < info->numbers)
	{
		sim->philos[i].fork[0] = sim->forks[(i + 0) % info->numbers];
		sim->philos[i].fork[1] = sim->forks[(i + 1) % info->numbers];
	}
	return (TRUE);
}

static t_bool	init_logic_objects(t_simulator *sim)
{
	const t_info	*info = &sim->info;
	int				i;
	t_philo			*philo;
	
	sim->philos = malloc(sizeof(t_philo) * info->numbers);
	sim->threads = malloc(sizeof(pthread_t) * info->numbers);
	sim->forks = malloc(sizeof(t_sync) * info->numbers);
	if (sim->philos == NULL || sim->threads == NULL || sim->forks == NULL)
		return (FALSE);
	i = -1;
	while (++i < info->numbers)
	{
		philo = &sim->philos[i];
		memset(philo, 0, sizeof(t_philo));
		philo->state = kThinking;
		philo->unique_id = i + 1;
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
	return (TRUE);
}

int		simulator_uninit(t_simulator *sim, int exit_code)
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
	if (sim->forks != NULL)
	{
		i = -1;
		while (++i < sim->info.numbers)
			sync_uninit(&sim->forks[i], kClose | kDestroy);
	}
	free(sim->philos);
	free(sim->threads);
	free(sim->forks);
	return (exit_code);
}