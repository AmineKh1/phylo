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


void	msleep(t_philo *ph, int sleep)
{
	int past;
	past = sleep - 20;
	usleep(past * 1000);
	gettimeofday(&ph->timepast, NULL);
	sleep = sleep + ph->increment;
	while(time_past(ph) < sleep)
	{
		usleep(150);
		gettimeofday(&ph->timepast, NULL);
	}
	ph->increment = time_past(ph);
}

int	time_past(t_philo *ph)
{
	int r;
	int past;
	past = ph->timepast.tv_sec * 1000 + ph->timepast.tv_usec / 1000;
	r = ph->time.tv_sec * 1000 + ph->time.tv_usec / 1000;
	return past - r;
}
int	time_past_die(t_philo *ph, int i)
{
	int r;
	int past;
	past = ph->end_die[i].tv_sec * 1000 + ph->end_die[i].tv_usec / 1000;
	r = ph->die_calcul[i].tv_sec * 1000 + ph->die_calcul[i].tv_usec / 1000;

	return past - r;
}
void*	act_philo(void *ph)
{
	int i;
	
	t_philo *p;
	p = (t_philo*) ph;
	i = p->i;
	int fork;
	int count = 0;
	int j;
	
	
	j = 0;
	while(j++ < p->tm_p_eat)
	{
		
		fork = i + 1;
		if (fork > p->nbr_philo - 1)
			fork = 0;
		if(i % 2 == 0)
		{
			pthread_mutex_lock(&p->mutex[fork]);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d has taken a fork\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			pthread_mutex_lock(&p->mutex[i]);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d has taken a fork\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			gettimeofday(&p->die_calcul[i], NULL);
			msleep(p, p->tm_eat);
			
			pthread_mutex_unlock(&p->mutex[fork]);
			pthread_mutex_unlock(&p->mutex[i]);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d is sleeping\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			msleep(p, p->tm_sleep);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d is thinking\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
		}
		else  
		{
			pthread_mutex_lock(&p->mutex[i]);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d has taken a fork\n",time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			pthread_mutex_lock(&p->mutex[fork]);
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d has taken a fork\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			gettimeofday(&p->die_calcul[i], NULL);
			msleep(p, p->tm_eat);

			pthread_mutex_unlock(&p->mutex[i]);
			pthread_mutex_unlock(&p->mutex[fork]);

			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d is sleeping\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
			msleep(p, p->tm_sleep);
	
			pthread_mutex_lock(&p->mutex_print);
			printf("%d %d is thinking\n", time_past(p), i + 1);
			pthread_mutex_unlock(&p->mutex_print);
		}
		// usleep(200);
	}
	p->end = p->end + 1;
	return 0;
}
// void*	die_sup(void *ph)
// {

// 	t_philo *p;
// 	int i;
// 	int time;
// 	p = (t_philo*) ph;
// 	i = -1;
// 	while(1)
// 	{
		
// 		while(++i < p->nbr_philo)
// 		{
// 			gettimeofday(&p->end_die[i], NULL);
// 			if(time_past_die(p, i) >= p->tm_die)
// 			{
// 				p->die = i;
				
// 			}

// 		}
// 		i = -1;
// 	}
// }
int	main(int argc, char **argv)
{
	if ( argc != 6)
	{
		perror("Error\n");
		return 1;
	}
	t_philo ph;

	
	ph.i = -1;
	ph.die = -1;
	ph.tm_die = atoi(argv[2]);	
	ph.tm_eat = atoi(argv[3]);
	ph.tm_sleep = atoi(argv[4]);
	ph.tm_p_eat = atoi(argv[5]);
	ph.nbr_philo = atoi(argv[1]);
	ph.nbr_forks = atoi(argv[1]);
	ph.end = 0;
	ph.increment = 0;
	ph.th_philo = malloc ((ph.nbr_philo) * sizeof(pthread_t));
	ph.mutex = malloc((ph.nbr_philo) * sizeof(pthread_mutex_t));
	ph.die_calcul = malloc((ph.nbr_philo) * sizeof(struct timeval));
	ph.end_die = malloc((ph.nbr_philo) * sizeof(struct timeval));
	while(++ph.i < ph.nbr_philo)
		pthread_mutex_init(&ph.mutex[ph.i], NULL);
	pthread_mutex_init(&ph.mutex_print, NULL);
	ph.i = -1;
	gettimeofday(&ph.time, NULL);
	gettimeofday(&ph.timepast, NULL);
	while(++ph.i < ph.nbr_philo)
		gettimeofday(&ph.die_calcul[ph.i], NULL);
	ph.i = -1;
	while (++ph.i < ph.nbr_philo)
	{
		
		pthread_create(&ph.th_philo[ph.i], NULL, &act_philo, &ph);
		usleep(50);
	}
	int i;
	i = -1;
	while(1)
	{
		
		while(++i < ph.nbr_philo)
		{
			gettimeofday(&ph.end_die[i], NULL);
			if(time_past_die(&ph, i) >= ph.tm_die)
			{
				gettimeofday(&ph.timepast, NULL);
				// pthread_mutex_unlock(&ph.mutex_print);
				pthread_mutex_lock(&ph.mutex_print);
				printf("%d %d died\n", time_past(&ph), i + 1);
				ph.i = -1;
				while(++ph.i < ph.nbr_philo)
				{
					pthread_detach(ph.th_philo[i]);
					pthread_mutex_destroy(&ph.mutex[ph.i]);
				}
				pthread_mutex_destroy(&ph.mutex_print);
				return 0;
			}
		}
		if (ph.end == ph.nbr_philo)
		{
			ph.i = -1;
			while(++ph.i < ph.nbr_philo)
			{
				pthread_detach(ph.th_philo[i]);
				pthread_mutex_destroy(&ph.mutex[ph.i]);
			}
			pthread_mutex_destroy(&ph.mutex_print);
			return 0;
		}
		usleep(100);
		i = -1;
	}
	return 0;
}