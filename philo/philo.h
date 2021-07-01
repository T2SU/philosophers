/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 19:43:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

enum e_philo_state
{
	kThinking,
	kEating,
	kSleeping,
	kDead
};

enum e_fork_state
{
	kNotUsing,
	kUsing
};

enum e_dir
{
	kLeft,
	kRight
};
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				unique_id;
	int				state;
}					t_fork;

typedef struct s_info
{
	int				numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
}					t_info;


typedef struct s_philo
{
	pthread_t		thread;
	int				unique_id;
	int				state;
	int				taken_forks;
	int				numbers_had_meal;
	t_fork			*pickable_forks[2];
	suseconds_t		last_meal;
	suseconds_t		state_end_time;
	t_info			info;
}					t_philo;

/*
** ============================================================================
**   [[ fork.c ]]
** ============================================================================
*/

t_bool		fork_try_take(t_fork *fork);
void		fork_put_down(t_fork *fork);

/*
** ============================================================================
**   [[ philo.c ]]
** ============================================================================
*/

t_bool		philo_change_state(t_philo *philo, int state);
void		philo_update(t_philo *philo);

/*
** ============================================================================
**   [[ table.c ]]
** ============================================================================
*/

t_bool		table_init(t_info info, t_fork **forks, t_philo **philos);
void		table_free(t_info info, t_fork **forks, t_philo **philos);

/*
** ============================================================================
**   [[ time.c ]]
** ============================================================================
*/

suseconds_t	time_get(void);

/*
** ============================================================================
**   [[ utils.c ]]
** ============================================================================
*/

void		ft_bzero(void *s, size_t n);
t_bool		ft_atoi_strict(const char *str, int *pvalue);

#endif
