/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:50:07 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 21:18:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_simulator	sim;

	if (!simulator_init(&sim, argc, argv))
		return (simulator_uninit(&sim, EXIT_FAILURE));
	context_begin(&sim);
	context_wait_to_end(&sim);
	return (simulator_uninit(&sim, EXIT_SUCCESS));
}
