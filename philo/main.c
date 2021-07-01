/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:04:18 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 20:27:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

t_info	parse_into_info(int argc, char *argv[])
{
	int		numbers;
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	if (argc < 5 || argc > 6)
		return (info);
	if (argc == 6 && !ft_atoi_strict(argv[5], &info.number_to_eat))
		return (info);
	if (ft_atoi_strict(argv[4], &info.time_to_sleep)
		&& ft_atoi_strict(argv[3], &info.time_to_eat)
		&& ft_atoi_strict(argv[2], &info.time_to_die)
		&& ft_atoi_strict(argv[1], &numbers))
		info.numbers = numbers;
	return (info);
}

static void	*philo_run(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (philo->state != kDead)
	{
		philo_update(philo);
		if (philo->info.number_to_eat > 0)
			if (philo->numbers_had_meal >= philo->info.number_to_eat)
				break ;
	}
	return (NULL);
}

static void	run_and_join_threads(t_philo *philos, int numbers)
{
	int	i;

	i = 0;
	while (i < numbers)
	{
		pthread_create(&philos[i].thread, NULL, &philo_run, &philos[i]);
		i++;
	}
	i = 0;
	while (i < numbers)
		pthread_join(philos[i++].thread, NULL);
}

int	main(int argc, char *argv[])
{
	const t_info	info = parse_into_info(argc, argv);
	t_philo			*philos;
	t_fork			*forks;
	int				ret_code;

	ret_code = EXIT_FAILURE;
	if (info.numbers > 0 && table_init(info, &forks, &philos))
	{
		run_and_join_threads(philos, info.numbers);
		ret_code = EXIT_SUCCESS;
	}
	table_free(info, &forks, &philos);
	return (ret_code);
}
