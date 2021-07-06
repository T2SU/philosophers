/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:41 by smun              #+#    #+#             */
/*   Updated: 2021/07/06 16:02:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	philo_init(int unique_id, t_philo *philo, t_info *info)
{
	memset(philo, 0, sizeof(t_philo));
	philo->state = kThinking;
	philo->unique_id = unique_id;
	philo->last_meal = time_get();
	philo->state_end_time = time_get();
	philo->info = info;
}
