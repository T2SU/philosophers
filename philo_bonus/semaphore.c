/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:48:52 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 15:15:29 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>

t_bool	semaphore_init(sem_t **psem, const char *name, int post_num)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644);
	if (sem == NULL)
		return (FALSE);
	while (post_num-- > 0)
		if (!sem_post(sem))
			return (FALSE);	
	*psem = sem;
	return (TRUE);
}

void	semaphore_close(sem_t *sem)
{
	sem_close(sem);
}

void	semaphore_uninit(const char *name)
{
	sem_unlink(name);
}
