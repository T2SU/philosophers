/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:06:39 by smun              #+#    #+#             */
/*   Updated: 2021/07/02 17:17:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Not parsable int?
**   1.  2 or more '-'
**   2.  too big or too small number ( < -2147483648  or  > 2147483647)
**   3.  non digit or dash
**   4.  only dash '-'
*/

t_bool	ft_atoi_strict(const char *str, int *pvalue)
{
	size_t		i;
	t_bool		neg;
	int			temp;

	neg = str[0] == '-';
	i = neg;
	if (str[neg] == '\0')
		return (FALSE);
	*pvalue = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		temp = str[i++] - '0';
		if (neg)
			temp = -temp;
		temp = 10 * *pvalue + temp;
		if (temp != *pvalue && (temp < *pvalue) != neg)
			return (FALSE);
		*pvalue = temp;
	}
	return (TRUE);
}
