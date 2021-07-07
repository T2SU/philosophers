/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

typedef int				t_bool;
typedef pthread_mutex_t	t_mutex;

enum	e_philo_state
{
	kThinking,
	kEating,
	kSleeping,
	kDead
};

typedef struct s_fork
{
	t_mutex		mutex;
	int			unique_id;
}				t_fork;

typedef struct s_info
{
	t_mutex		mutex;
	int			died_count;
	int			numbers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	t_bool		specified_number_to_eat;
	int			number_to_eat;
}				t_info;

typedef struct s_philo
{
	pthread_t	thread;
	int			unique_id;
	int			state;
	int			numbers_had_meal;
	t_fork		*prioritized_forks[2];
	time_t		last_meal;
	time_t		state_end_time;
	t_info		*info;
}				t_philo;

/*
** ============================================================================
**   [[ fork.c ]]
** ============================================================================
*/

t_bool			fork_init(int unique_id, t_fork *fork);
void			prioritize_forks(int numbers, t_philo *philo, t_fork *forks);
t_bool			fork_is_same(t_fork *forks[]);
void			fork_try_to_take(t_fork *fork);
void			fork_put_down(t_fork *fork);

/*
** ============================================================================
**   [[ philo_init.c ]]
** ============================================================================
*/

void			philo_init(int unique_id, t_philo *philo, t_info *info);

/*
** ============================================================================
**   [[ philo.c ]]
** ============================================================================
*/

void			philo_update(t_philo *philo);

/*
** ============================================================================
**   [[ thread.c ]]
** ============================================================================
*/

void			thread_philosophers_begin(t_philo *philos, int numbers);
void			thread_philosophers_join(t_philo *philos, int numbers);

/*
** ============================================================================
**   [[ utils.c ]]
** ============================================================================
*/

time_t			time_get(void);
t_bool			ft_atoi_strict(const char *str, int *pvalue);

/*
** ============================================================================
**   [[ info.c ]]
** ============================================================================
*/

t_bool			info_parse_details(t_info *info, int argc, char *argv[]);
void			info_increase_died_count(t_info *info);
int				info_get_died_count(t_info *info);

/*
** ============================================================================
**   [[ print.c ]]
** ============================================================================
*/

t_bool			print_init(void);
void			print_state(int unique_id, int state, const time_t time);
void			print_fork(int unique_id, const time_t time);
void			print_close(void);

#endif
