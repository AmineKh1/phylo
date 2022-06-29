/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:45:22 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 11:46:08 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	calcule(const char *nptr, int sign)
{
	unsigned long	r;

	r = 0;
	if (*nptr < '0' || *nptr > '9')
		return (-2);
	while (*nptr >= '0' && *nptr <= '9')
	{
		r = r * 10;
		r = r + (*nptr - '0');
		nptr++;
	}
	if ((*nptr < '0' || *nptr > '9') && *nptr != '\0')
		return (-2);
	if ((r > 2147483647 && sign == 1) || (r > 2147483648 && sign == -1))
		return (-2);
	return ((int)r * sign);
}

int	ft_atoi(const char *nptr)
{
	unsigned long	r;
	int				signe;

	r = 0;
	signe = 1;
	if (*nptr == '-')
		return (-2);
	else if (*nptr == '+')
		return (-2);
	r = calcule(nptr, signe);
	return (r);
}
