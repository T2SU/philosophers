/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:43:20 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 12:47:08 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	info_increase_died_count(t_info *info)
{
	pthread_mutex_lock(&info->mutex);
	(info->died_count)++;
	pthread_mutex_unlock(&info->mutex);
}

int		info_get_died_count(t_info *info)
{
	int	ret;

	pthread_mutex_lock(&info->mutex);
	ret = info->died_count;
	pthread_mutex_unlock(&info->mutex);
	return (ret);
}
