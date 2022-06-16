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
	int past;
	past = sleep * 90 / 100;
	// gettimeofday(&ph->time, NULL);
	usleep(sleep * 1000);
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
void*	act_philo(void *it)
{

	// t_philo p;
	int i;
	// p = *(t_philo*) ph;
	i = *(int *) it;
		printf(" %d has taken a fork\n", i);
	// printf("%d\n", i);
	return 0;
}
int	main(int argc, char **argv)
{
	if ( argc != 5 || atoi(argv[1]) < 1)
	{
		perror("Error\n");
	}
	t_philo ph;
	
	gettimeofday(&ph.time, NULL);
	ph.i = -1;
	ph.tm_die = atoi(argv[2]);	
	ph.tm_eat = atoi(argv[3]);
	ph.tm_sleep = atoi(argv[4]);
	ph.tm_p_eat = atoi(argv[6]);
	ph.nbr_philo = atoi(argv[1]);
	ph.nbr_forks = atoi(argv[1]);
	ph.th_philo = malloc ((ph.nbr_philo) * sizeof(pthread_t));
	pthread_mutex_init(&ph.mutex, NULL);
	while (++ph.i <= ph.nbr_philo)
	{
		int* i = malloc(4);
		*i = ph.i;
		pthread_create(&ph.th_philo[ph.i], NULL, &act_philo, i);
	}
	while(1);
	
	
}