/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:06:56 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 11:58:37 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_philo *ph)
{
	while (++ph->i < ph->nbr_philo)
	{
		if (pthread_mutex_init(&ph->mutex[ph->i], NULL) != 0)
		{
			mutex_destroy_forks(ph);
			return (1);
		}
	}
	if (pthread_mutex_init(&ph->mutex_print, NULL) != 0)
	{
		destroy_mutex(ph);
		return (1);
	}
	gettimeofday(&ph->time, NULL);
	gettimeofday(&ph->timepast, NULL);
	ph->i = -1;
	while (++ph->i < ph->nbr_philo)
		gettimeofday(&ph->die_calcul[ph->i], NULL);
	return (0);
}

int	create_thread(t_philo *ph)
{
	ph->i = -1;
	while (++ph->i < ph->nbr_philo)
	{
		if (pthread_create(&ph->th_philo[ph->i], NULL, &act_philo, ph) != 0)
		{	
			destroy_mutex(ph);
			return (1);
		}
		usleep(100);
	}
	ph->i = -1;
	while (++ph->i < ph->nbr_philo)
	{
		if (pthread_detach(ph->th_philo[ph->i]) != 0)
		{
			destroy_mutex(ph);
			return (1);
		}
	}
	return (0);
}

int	spv_die(t_philo *ph, int i)
{
	while (1)
	{
		i = -1;
		usleep(300);
		while (++i < ph->nbr_philo)
		{
			gettimeofday(&ph->end_die[i], NULL);
			if (time_past(ph->die_calcul[i], ph->end_die[i]) >= ph->tm_die)
			{
				gettimeofday(&ph->timepast, NULL);
				pthread_mutex_lock(&ph->mutex_print);
				printf("%d %d died\n", time_past(ph->time, ph->timepast), i + 1);
				destroy_mutex(ph);
				return (0);
			}
		}
		if (ph->end == ph->nbr_philo)
		{
			destroy_mutex(ph);
			return (0);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (1);
	if (init_var(ph, argv, argc) == 1)
		return (1);
	if (create_mutex(ph) == 1)
		return (1);
	if (create_thread(ph) == 1)
		return (1);
	return (spv_die(ph, i));
}
