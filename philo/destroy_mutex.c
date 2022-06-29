/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:18:09 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 10:33:47 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_forks(t_philo *ph)
{
	int	j;

	j = -1;
	while (++j < ph->i)
		pthread_mutex_destroy(&ph->mutex[j]);
}

void	destroy_mutex(t_philo *ph)
{
	int	j;

	j = -1;
	pthread_mutex_destroy(&ph->mutex_print);
	while (++j < ph->i)
		pthread_mutex_destroy(&ph->mutex[j]);
}
