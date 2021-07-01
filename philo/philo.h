/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 13:49:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

typedef int			t_bool;

enum				e_philo_state
{
	kThinking,
	kEating,
	kSleeping,
	kDead
};

enum				e_fork_state
{
	kNotUsing,
	kUsing
};

enum				e_dir
{
	kLeft,
	kRight
};

typedef struct		s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				state;
	suseconds_t		begin_time;
}					t_philo;

typedef struct		s_fork
{
	pthread_mutex_t	mutex;
	int				unique_id;
	int				state;
}					t_fork;

typedef struct		s_table
{
	pthread_mutex_t	mutex;
	int				numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	t_philo			*philosophers;
	t_fork			*forks;
}					t_table;
// 1 f 2 f 3 f 4 f 5
/*
** ============================================================================
**   [[ .c ]]
** ============================================================================
*/

/*
** ============================================================================
**   [[ time.c ]]
** ============================================================================
*/

#endif
