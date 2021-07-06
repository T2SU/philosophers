/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:47:36 by smun              #+#    #+#             */
/*   Updated: 2021/07/06 16:19:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

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
	int			unique_id;
	int			state;
	int			numbers_had_meal;
	time_t		last_meal;
	time_t		state_end_time;
	t_info		*info;
}				t_philo;

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

#endif
