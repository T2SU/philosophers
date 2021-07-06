/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:58:47 by smun              #+#    #+#             */
/*   Updated: 2021/07/06 19:31:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

void	*sub_process(void *ptr)
{
	sem_t *sem = (sem_t *)ptr;
	int status;
	pid_t pid = fork();
	if (pid != 0)
		waitpid(pid, &status, 0);
	else
	{
		sem_wait(sem);
		printf("taken semaphore!\n");
		sem_post(sem);
	}
	return (NULL);
}

int	main(void)
{
	sem_t	*sem;

	sem = sem_open("philo_bonus", O_CREAT, 0644);
	if (sem == NULL)
	{
		printf("error creating sem\n");	
		return (EXIT_FAILURE);
	}
	sem_post(sem); // inc value
	
	pthread_t threads[5];
	int sz = sizeof(threads) / sizeof(pthread_t);
	for (int i = 0; i < sz; i++)
		pthread_create(&threads[i], NULL, sub_process, sem);
	
	for (int i = 0; i < sz; i++)
		pthread_join(threads[i], NULL);
	
	sem_close(sem);
	
	printf("end for wait\n");
	
	return (0);
}
