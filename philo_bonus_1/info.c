/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:43:20 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:46:35 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

t_bool	info_parse_details(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
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
	return (TRUE);
}

t_bool	info_init_monitor_semaphore(t_info *info)
{
	info->sem_monitor = sem_open(SEM_NAME_MONITOR, O_CREAT, 0644);
	if (info->sem_monitor == NULL)
		return (FALSE);
	if (!sem_post(info->sem_monitor))
		return (FALSE);
	return (TRUE);
}

void	info_increase_died_count(t_info *info)
{
	sem_wait(info->sem_monitor);
	(info->died_count)++;
	sem_post(info->sem_monitor);
}

int	info_get_died_count(t_info *info)
{
	int	ret;

	sem_wait(info->sem_monitor);
	ret = info->died_count;
	sem_post(info->sem_monitor);
	return (ret);
}
