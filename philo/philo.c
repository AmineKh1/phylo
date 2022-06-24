/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   philo.c                                           :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: akhouya <akhouya@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: Invalid date        by                 #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/06/24 10:47:05 by akhouya      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include "philo.h"

void	 msleep(int sleep)
{
	int past;
	struct timeval before;
	struct timeval after;
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

int time_past(struct timeval before, struct timeval after)
{
	int r;
	int past;

	past = after.tv_sec * 1000 + after.tv_usec / 1000;
	r = before.tv_sec * 1000 + before.tv_usec / 1000;
	r = past - r;
	return (r);
}

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		perror("Error\n");
		return (1);
	}
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (1);
	ph->tm_die = atoi(argv[2]);
	ph->tm_eat = atoi(argv[3]);
	ph->tm_sleep = atoi(argv[4]);
	ph->nbr_philo = atoi(argv[1]);
	ph->tm_p_eat = -1;
	ph->die = -1;
	ph->end = 0;
	if (argc == 6)
		ph->tm_p_eat = atoi(argv[5]);
	ph->th_philo = malloc((ph->nbr_philo) * sizeof(pthread_t));
	ph->mutex = malloc((ph->nbr_philo) * sizeof(pthread_mutex_t));
	ph->die_calcul = malloc((ph->nbr_philo) * sizeof(struct timeval));
	ph->end_die = malloc((ph->nbr_philo) * sizeof(struct timeval));

	if (!ph->th_philo || !ph->mutex || !ph->die_calcul)
		return 1;
	ph->i = -1;
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
	if( gettimeofday(&ph->time, NULL) == -1 || gettimeofday(&ph->timepast, NULL) == -1)
	{	
		destroy_mutex(ph);
		return (1);
	}
	ph->i = -1;
	while(++ph->i < ph->nbr_philo)
	{
		if(gettimeofday(&ph->die_calcul[ph->i], NULL) != 0)
		{
			destroy_mutex(ph);
			return (1);
		}
	}
	ph->i = -1;
	while(++ph->i < ph->nbr_philo)
	{
		if(pthread_create(&ph->th_philo[ph->i], NULL, &act_philo, ph) != 0)
		{	
			destroy_mutex(ph);
			return (1);
		}
		usleep(40);
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
	int i;
	i = 0;
	while(1)
	{
		i = -1;
		while(++i < ph->nbr_philo)
		{
			gettimeofday(&ph->end_die[i], NULL);
			{
				if (time_past(ph->die_calcul[i], ph->end_die[i]) >= ph->tm_die)
				{
					gettimeofday(&ph->timepast, NULL);
					pthread_mutex_unlock(&ph->mutex_print);
					pthread_mutex_lock(&ph->mutex_print);
					printf("%d %d died\n", time_past(ph->time, ph->timepast), i + 1);
					destroy_mutex(ph);
					return 0;
				}

			}
		}
		if (ph->end == ph->nbr_philo)
		{
			destroy_mutex(ph);
			return 0;
		}
	}
}
