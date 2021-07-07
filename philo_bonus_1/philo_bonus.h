/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# define TRUE 1
# define FALSE 0
# define SEM_NAME_PHILO "philo_bonus"
# define SEM_NAME_MONITOR "philo_bonus_monitor"
# define SEM_NAME_PRINT "philo_bonus_print"

typedef int				t_bool;

enum	e_philo_state
{
	kThinking,
	kEating,
	kSleeping,
	kDead
};

typedef struct s_info
{
	sem_t	*semaphore;
	sem_t	*sem_monitor;
	int		died_count;
	int		numbers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_bool	specified_number_to_eat;
	int		number_to_eat;
}			t_info;

typedef struct s_philo
{
	int		unique_id;
	int		state;
	int		numbers_had_meal;
	time_t	last_meal;
	time_t	state_end_time;
	t_info	*info;
}			t_philo;

/*
** ============================================================================
**   [[ utils.c ]]
** ============================================================================
*/

time_t		time_get(void);
t_bool		ft_atoi_strict(const char *str, int *pvalue);

/*
** ============================================================================
**   [[ info.c ]]
** ============================================================================
*/

t_bool		info_parse_details(t_info *info, int argc, char *argv[]);
t_bool		info_init_monitor_semaphore(t_info *info);
void		info_increase_died_count(t_info *info);
int			info_get_died_count(t_info *info);

/*
** ============================================================================
**   [[ print.c ]]
** ============================================================================
*/

t_bool		print_init(void);
void		print_close(void);
void		print_state(int unique_id, int state, const time_t time);
void		print_fork(int unique_id, const time_t time);

/*
** ============================================================================
**   [[ semaphore.c ]]
** ============================================================================
*/

t_bool		semaphore_init(sem_t **psem, const char *name, int post_num);
void		semaphore_close(sem_t *sem);
void		semaphore_uninit(const char *name);

/*
** ============================================================================
**   [[ philo_fork.c ]]
** ============================================================================
*/

void		philo_try_to_take_fork(t_philo *philo);
void		philo_put_down_fork(t_philo *philo);

/*
** ============================================================================
**   [[ philo_init.c ]]
** ============================================================================
*/

void		philo_init(int unique_id, t_philo *philo, t_info *info);

/*
** ============================================================================
**   [[ philo.c ]]
** ============================================================================
*/

void		philo_update(t_philo *philo);

/*
** ============================================================================
**   [[ process.c ]]
** ============================================================================
*/

void		process_child_begin(pthread_t *threads, t_philo *philos, int n);
void		process_child_join(pthread_t *threads, int n);

#endif
