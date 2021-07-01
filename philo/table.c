/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:48:30 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 15:24:26 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

t_bool	init_table(int numbers, t_table *table)
{
	table->numbers = numbers;
	table->philosophers = malloc(sizeof(t_philo) * numbers);
	table->forks = malloc(sizeof(t_fork) * numbers);
	if (table->philosophers == NULL)
		return (FALSE);
	if (table->forks == NULL)
		return (FALSE);
}

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		pthread_mutex_destroy(&table->philosophers[i].mutex);
		i++;
	}
	free(table->forks);
	free(table->philosophers);
}
