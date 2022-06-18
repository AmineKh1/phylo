/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:03:44 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/15 13:57:10 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	msleep(t_philo *ph, int sleep)
{
	// int sleep;

	// if (slp == 's')
	// {
	// 	sleep = ph->tm_sleep;
	// }
	// else if (slp == 'e')
	// 	sleep = ph->tm_eat;
	int past;
	// gettimeofday(&ph->time, NULL);
	past = sleep - 20;
	usleep(past * 1000);
	gettimeofday(&ph->timepast, NULL);
	while(time_past(ph) < 200)
	{
		usleep(1);
		gettimeofday(&ph->timepast, NULL);
	}
	return time_past(ph);
}
int	time_past(t_philo *ph)
{
	int r;
	int past;

	past = ph->timepast.tv_sec * 1000 + ph->timepast.tv_usec / 1000;
	r = ph->time.tv_sec * 1000 + ph->time.tv_usec / 1000;
	return past - r;
}
void*	act_philo(void *ph)
{

	t_philo *p;
	int i;
	int fork;
	int j;
	p = (t_philo*) ph;
	i = p->i + 1;
	j = 0;
	while(j++ < p->tm_p_eat)
	{
		fork = i + 1;
		if (fork > p->nbr_philo)
			fork = 1;
		if(i % 2 == 0)
		{
			pthread_mutex_lock(&p->mutex[fork]);
			printf("%d %d has taken a fork %d\n", msleep(p, p->tm_eat), i, fork);
			pthread_mutex_lock(&p->mutex[i]);
			printf("%d %d has taken a fork %d\n", msleep(p, p->tm_eat), i, i);
			pthread_mutex_unlock(&p->mutex[fork]);
			pthread_mutex_unlock(&p->mutex[i]);
			printf("%d %d is sleeping\n", msleep(p, p->tm_eat), i);
		}
		else
		{
			pthread_mutex_lock(&p->mutex[i]);
			printf("%d %d has taken a fork %d\n",msleep(p, p->tm_eat), i, i);
			
			pthread_mutex_lock(&p->mutex[fork]);
			printf("%d %d has taken a fork %d\n",msleep(p, p->tm_eat), i, fork);
			pthread_mutex_unlock(&p->mutex[i]);
			pthread_mutex_unlock(&p->mutex[fork]);
			printf("%d %d is sleeping\n",msleep(p, p->tm_sleep), i);
		}
	}
	p->end++;
	// printf("%d\n", i);
	return 0;
}
int	main(int argc, char **argv)
{
	if ( argc != 6)
	{
		perror("Error\n");
		return 1;
	}
	t_philo ph;

	
	ph.i = -1;
	time_past = 0;
	ph.tm_die = atoi(argv[2]);	
	ph.tm_eat = atoi(argv[3]);
	ph.tm_sleep = atoi(argv[4]);
	ph.tm_p_eat = atoi(argv[5]);
	ph.nbr_philo = atoi(argv[1]);
	ph.nbr_forks = atoi(argv[1]);
	ph.end = 0;
	ph.th_philo = malloc ((ph.nbr_philo) * sizeof(pthread_t));
	ph.mutex = malloc((ph.nbr_philo) * sizeof(pthread_mutex_t));
	while(++ph.i < ph.nbr_philo)
		pthread_mutex_init(&ph.mutex[ph.i], NULL);
	ph.i = -1;
	gettimeofday(&ph.time, NULL);
	while (++ph.i < ph.nbr_philo)
	{
		
		pthread_create(&ph.th_philo[ph.i], NULL, &act_philo, &ph);
		usleep(50);
	}
	while(1)
	{
		if(ph.end == ph.nbr_philo)
			exit(1);
	}
}