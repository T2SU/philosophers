/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:06:39 by smun              #+#    #+#             */
/*   Updated: 2021/07/01 15:19:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			*dest_large;
	size_t			i;

	dest = (unsigned char *)s;
	i = n % sizeof(size_t);
	while (i--)
		*(dest++) = 0;
	dest_large = (size_t *)dest;
	i = n / sizeof(size_t);
	while (i--)
		*(dest_large++) = 0;
}
