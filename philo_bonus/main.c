/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:58:47 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <pthread.h>

/*
** No initializing about forks. (did in mandatory part.)
*/

static t_bool	init_objects(t_info *info, t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < info->numbers)
	{
		philo_init(i + 1, &philos[i], info);
	}
	return (TRUE);
}

/*
** No initializing about forks. (did in mandatory part.)
*/

static t_bool	init_static_variables(void)
{
	if (!print_init())
		return (FALSE);
	time_get();
	return (TRUE);
}

/*
** Not doing about forks. (did in mandatory part.)
** However, do heap-free array of monitor threads.
*/

static int	app_exit(t_info *info, pthread_t *trds, t_philo *philos, int ret)
{
	int	i;

	if (philos != NULL)
	{
		i = -1;
		while (++i < info->numbers)
			philos[i].state = kDead;
	}
	print_close();
	semaphore_uninit(SEM_NAME_PRINT);
	semaphore_uninit(SEM_NAME_MONITOR);
	semaphore_uninit(SEM_NAME_PHILO);
	free(philos);
	free(trds);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_philo		*philos;
	pthread_t	*threads;

	if (!info_parse_details(&info, argc, argv))
		return (app_exit(&info, NULL, NULL, EXIT_FAILURE));
	if (!info_init_monitor_semaphore(&info))
		return (app_exit(&info, NULL, NULL, EXIT_FAILURE));
	philos = malloc(sizeof(t_philo) * info.numbers);
	threads = malloc(sizeof(pthread_t) * info.numbers);
	if (philos == NULL || threads == NULL)
		return (app_exit(&info, threads, philos, EXIT_FAILURE));
	if (!init_objects(&info, philos))
		return (app_exit(&info, threads, philos, EXIT_FAILURE));
	if (!init_static_variables())
		return (app_exit(&info, threads, philos, EXIT_FAILURE));
	process_child_begin(threads, philos, info.numbers);
	return (app_exit(&info, threads, philos, EXIT_SUCCESS));
}
