/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:29:05 by smun              #+#    #+#             */
/*   Updated: 2021/07/09 21:08:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*context_run(void *p_ctx)
{
	t_context	*ctx;

	ctx = (t_context *)p_ctx;
	context_update(ctx);
	if (ctx->philo->state == kDead)
		monitor_set_state(ctx->monitor, kInterrupted);
	return (NULL);
}
