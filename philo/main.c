/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:04:18 by smun              #+#    #+#             */
/*   Updated: 2021/07/06 16:00:56 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

static t_bool	init_objects(t_info *info, t_fork *forks, t_philo *philos)
{
	int			i;

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

static t_bool	init_static_variables(void)
{
	if (!print_init())
		return (FALSE);
	time_get();
	return (TRUE);
}

static int	app_exit(t_info *info, t_fork *forks, t_philo *philos, int ret)
{
	int	i;

	if (philos != NULL)
	{
		i = -1;
		while (++i < info->numbers)
			philos[i].state = kDead;
	}
	if (forks != NULL)
	{
		i = -1;
		while (++i < info->numbers)
			pthread_mutex_destroy(&forks[i].mutex);
	}
	pthread_mutex_destroy(&info->mutex);
	print_uninit();
	free(forks);
	free(philos);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philos;
	t_fork	*forks;

	if (!info_parse_details(&info, argc, argv))
		return (app_exit(&info, NULL, NULL, EXIT_FAILURE));
	philos = malloc(sizeof(t_philo) * info.numbers);
	forks = malloc(sizeof(t_fork) * info.numbers);
	if (philos == NULL || forks == NULL)
		return (app_exit(&info, forks, philos, EXIT_FAILURE));
	if (!init_objects(&info, forks, philos))
		return (app_exit(&info, forks, philos, EXIT_FAILURE));
	if (!init_static_variables())
		return (app_exit(&info, forks, philos, EXIT_FAILURE));
	thread_philosophers_begin(philos, info.numbers);
	thread_philosophers_join(philos, info.numbers);
	return (app_exit(&info, forks, philos, EXIT_SUCCESS));
}
