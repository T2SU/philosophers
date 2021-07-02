/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:43:20 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 15:45:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	info_new_simulation_details(t_info *info, int argc, char *argv[])
{
	ft_bzero(info, sizeof(t_info));
	if (argc < 5 || argc > 6)
		return (FALSE);
	info->specified_number_to_eat = (argc == 6);
	if (argc == 6 && !ft_atoi_strict(argv[5], &info->number_to_eat))
		return (FALSE);
	if (0 != pthread_mutex_init(&info->mutex, NULL))
		return (FALSE);
	if (!ft_atoi_strict(argv[4], &info->time_to_sleep))
		return (FALSE);
	if (!ft_atoi_strict(argv[3], &info->time_to_eat))
		return (FALSE);
	if (!ft_atoi_strict(argv[2], &info->time_to_die))
		return (FALSE);
	if (!ft_atoi_strict(argv[1], &info->numbers))
		return (FALSE);
	return (TRUE);
}

void	info_increase_died_count(t_info *info)
{
	pthread_mutex_lock(&info->mutex);
	(info->died_count)++;
	pthread_mutex_unlock(&info->mutex);
}

int	info_get_died_count(t_info *info)
{
	int	ret;

	pthread_mutex_lock(&info->mutex);
	ret = info->died_count;
	pthread_mutex_unlock(&info->mutex);
	return (ret);
}
