/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:04:18 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 12:48:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

static t_info	make_simulation_info(int argc, char *argv[])
{
	int		numbers;
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	if (argc < 5 || argc > 6)
		return (info);
	if (argc == 6 && !ft_atoi_strict(argv[5], &info.number_to_eat))
		return (info);
	if (0 != pthread_mutex_init(&info.mutex, NULL))
		return (info);
	if (ft_atoi_strict(argv[4], &info.time_to_sleep)
		&& ft_atoi_strict(argv[3], &info.time_to_eat)
		&& ft_atoi_strict(argv[2], &info.time_to_die)
		&& ft_atoi_strict(argv[1], &numbers))
		info.numbers = numbers;
	return (info);
}

static t_bool	init_static_variables(void)
{
	if (!philo_change_state(NULL, 0, 0))
		return (FALSE);
	time_get();
	return (TRUE);
}

static t_bool	init_objects(t_info *info, t_fork *forks, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < info->numbers)
	{
		if (!fork_init(i + 1, &forks[i]))
			return (FALSE);
		philo_init(i + 1, &philos[i], info);
	}
	i = -1;
	while (++i < info->numbers)
		specify_forks_to_pick(info->numbers, &philos[i], forks);
	return (TRUE);
}

static int	free_objects(t_info *info, t_fork *forks, t_philo *philos, int ret)
{
	int	i;

	i = 0;
	while (i < info->numbers)
		philos[i++].state = kDead;
	i = 0;
	while (i < info->numbers)
		pthread_mutex_destroy(&forks[i++].mutex);
	pthread_mutex_destroy(&info->mutex);
	free(forks);
	free(philos);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_info			info;
	t_philo			*philos;
	t_fork			*forks;

	info = make_simulation_info(argc, argv);
	philos = malloc(sizeof(t_philo) * info.numbers);
	forks = malloc(sizeof(t_fork) * info.numbers);
	if (info.numbers == 0
		|| philos == NULL
		|| forks == NULL
		|| !init_objects(&info, forks, philos)
		|| !init_static_variables())
		return (free_objects(&info, forks, philos, EXIT_FAILURE));
	thread_run_and_join(philos, info.numbers);
	return (free_objects(&info, forks, philos, EXIT_SUCCESS));
}
