/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/18 21:32:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

enum	e_philo_state
{
	kThinking,
	kEating,
	kSleeping,
	kDead
};

enum	e_monitor_state
{
	kNormal,
	kInterrupted
};

enum	e_sync_type
{
	kMonitor,
	kPrinter,
	kPhilosopher
};

/*
** CriticalSection Structures.
** Defined by each project. (mandatory/bonus)
*/

typedef struct s_sync
{
	pthread_mutex_t	mutex;
}					t_sync;

typedef struct s_fork
{	
	t_sync	sync;
	int		counter;
	t_bool	using;
}			t_fork;

/*
** Logic Structures
*/

typedef struct s_info
{
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
	t_fork	*fork[2];
	int		state;
	int		taken;
	int		numbers_had_meal;
	time_t	last_meal;
	time_t	state_end_time;
}			t_philo;

typedef struct s_monitor
{
	t_sync	sync;
	int		state;
}			t_monitor;

typedef struct s_printer
{
	t_sync	sync;
}			t_printer;

typedef struct s_context
{
	t_philo			*philo;
	t_info			*info;
	t_printer		*printer;
	t_monitor		*monitor;
	pthread_t		thread;
}					t_context;

typedef struct s_simulator
{
	t_info		info;
	t_printer	printer;
	t_monitor	monitor;
	t_philo		*philos;
	t_fork		*forks;
	t_context	*contexts;
}				t_simulator;

/*
** ============================================================================
**   [[ simulator.c ]]
** ============================================================================
*/

t_bool	simulator_init(t_simulator *simulator, int argc, char *argv[]);
int		simulator_uninit(t_simulator *simulator, int exit_code);

/*
** ============================================================================
**   [[ sync_[implementation].c ]]  (semaphore/mutex)
** ============================================================================
*/

t_bool	sync_init(t_sync *sync);
void	sync_uninit(t_sync *sync);
void	sync_lock(t_sync *sync);
void	sync_unlock(t_sync *sync);

/*
** ============================================================================
**   [[ printer.c ]]
** ============================================================================
*/

void	printer_set(t_printer *printer);
void	printer_print(const char *mes);
void	printer_changed_state(int philo_id, int state, const time_t time);
void	printer_taken_fork(int philo_id, const time_t time);

/*
** ============================================================================
**   [[ monitor.c ]]
** ============================================================================
*/

int		monitor_get_state(t_monitor *mon);
void	monitor_set_state(t_monitor *mon, int state);

/*
** ============================================================================
**   [[ context.c ]]
** ============================================================================
*/

void	context_update(t_context *ctx);
void	context_begin(t_simulator *sim);
void	context_wait_to_end(t_simulator *sim);

/*
** ============================================================================
**   [[ context_[implementation].c ]] (process/thread)
** ============================================================================
*/

void	*context_run(void *p_ctx);

/*
** ============================================================================
**   [[ philo_life.c ]]
** ============================================================================
*/

void	philo_update_survive(t_philo *philo, t_context *ctx, const time_t time);

/*
** ============================================================================
**   [[ philo_forks.c ]]
** ============================================================================
*/

t_bool	philo_forks_try_take(t_philo *philo);
void	philo_forks_put_down(t_philo *philo);

/*
** ============================================================================
**   [[ philo.c ]]
** ============================================================================
*/

void	philo_change_state(t_philo *philo, int state, time_t time);
void	philo_drop_the_forks(t_philo *philo);
void	philo_update_state(t_philo *philo, t_context *ctx, const time_t time);

/*
** ============================================================================
**   [[ utils.c ]]
** ============================================================================
*/

time_t	time_get(void);
t_bool	ft_atoi_strict(const char *str, int *pvalue);

#endif
