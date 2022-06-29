/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:07:09 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 12:17:28 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int sleep)
{
	int				past;
	struct timeval	before;
	struct timeval	after;

	past = sleep - 30;
	gettimeofday(&before, NULL);
	usleep(past * 1000);
	gettimeofday(&after, NULL);
	while (time_past(before, after) < sleep)
	{
		usleep(100);
		gettimeofday(&after, NULL);
	}
}

int	time_past(struct timeval before, struct timeval after)
{
	int	r;
	int	past;

	past = after.tv_sec * 1000 + after.tv_usec / 1000;
	r = before.tv_sec * 1000 + before.tv_usec / 1000;
	r = past - r;
	return (r);
}

int	init_var(t_philo *ph, char **argv, int argc)
{
	ph->tm_die = ft_atoi(argv[2]);
	ph->tm_eat = ft_atoi(argv[3]);
	ph->tm_sleep = ft_atoi(argv[4]);
	ph->nbr_philo = ft_atoi(argv[1]);
	ph->tm_p_eat = -1;
	ph->die = -1;
	ph->end = 0;
	ph->i = -1;
	if (argc == 6)
		ph->tm_p_eat = ft_atoi(argv[5]);
	if (ph->tm_die == -2 || ph->tm_eat == -2 || ph->tm_sleep == -2
		|| ph->tm_p_eat == -2 || ph->nbr_philo == -2)
		return (1);
	ph->th_philo = malloc((ph->nbr_philo) * sizeof(pthread_t));
	ph->mutex = malloc((ph->nbr_philo) * sizeof(pthread_mutex_t));
	ph->die_calcul = malloc((ph->nbr_philo) * sizeof(struct timeval));
	ph->end_die = malloc((ph->nbr_philo) * sizeof(struct timeval));
	if (!ph->th_philo || !ph->mutex || !ph->die_calcul || !ph->end_die)
		return (1);
	if (ph->tm_die == -2 || ph->tm_eat == -2 || ph->tm_sleep == -2
		|| ph->tm_p_eat == -2 || ph->nbr_philo == -2)
		return (1);
	return (0);
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
