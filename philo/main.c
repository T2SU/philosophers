/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:04:18 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 15:46:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

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
		prioritize_forks(info->numbers, &philos[i], forks);
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

	philos = malloc(sizeof(t_philo) * info.numbers);
	forks = malloc(sizeof(t_fork) * info.numbers);
	if (philos == NULL || forks == NULL)
		return (free_objects(&info, forks, philos, EXIT_FAILURE));
	if (!info_new_simulation_details(&info, argc, argv))
		return (free_objects(&info, forks, philos, EXIT_FAILURE));
	if (!init_objects(&info, forks, philos))
		return (free_objects(&info, forks, philos, EXIT_FAILURE));
	if (!init_static_variables())
		return (free_objects(&info, forks, philos, EXIT_FAILURE));
	thread_philosophers_begin(philos, info.numbers);
	thread_philosophers_join(philos, info.numbers);
	return (free_objects(&info, forks, philos, EXIT_SUCCESS));
}
