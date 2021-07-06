/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:43:20 by smun              #+#    #+#             */
/*   Updated: 2021/07/06 16:19:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>
#include <pthread.h>

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
