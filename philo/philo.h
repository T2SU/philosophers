/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 14:25:04 by smun             ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				unique_id;
	int				state;
}					t_fork;

typedef struct s_info
{
	pthread_mutex_t	mutex;
	int				died_count;
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
	int				numbers_had_meal;
	int				taken_forks;
	t_fork			*prioritized_forks[2];
	time_t			last_meal;
	time_t			state_end_time;
	t_info			*info;
}					t_philo;

/*
** ============================================================================
**   [[ fork.c ]]
** ============================================================================
*/

t_bool		fork_init(int unique_id, t_fork *fork);
void		prioritize_forks_to_pick(int numbers, t_philo *philo, t_fork *forks);
t_bool		fork_is_same(t_fork *forks[]);
t_bool		fork_try_to_take(t_fork *fork);
void		fork_put_down(t_fork *fork);

/*
** ============================================================================
**   [[ philo.c ]]
** ============================================================================
*/

void		philo_init(int unique_id, t_philo *philo, t_info *info);
t_bool		philo_change_state(t_philo *philo, int state, const time_t time);
void		philo_update(t_philo *philo);

/*
** ============================================================================
**   [[ time.c ]]
** ============================================================================
*/

time_t		time_get(void);

/*
** ============================================================================
**   [[ thread.c ]]
** ============================================================================
*/

void		thread_run_and_join(t_philo *philos, int numbers);

/*
** ============================================================================
**   [[ utils.c ]]
** ============================================================================
*/

void		ft_bzero(void *s, size_t n);
t_bool		ft_atoi_strict(const char *str, int *pvalue);

/*
** ============================================================================
**   [[ info.c ]]
** ============================================================================
*/

void		info_increase_died_count(t_info *info);
int			info_get_died_count(t_info *info);

#endif
