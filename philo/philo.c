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

// int	time_past(t_philo p)
// {
	
// }
void*	act_philo(void *ph)
{
	t_philo p;
	p = *(t_philo*) ph;
	printf("%d\n", p.i);
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
	printf("%ld\n%d\n", ph.time.tv_sec, ph.time.tv_usec);
	exit(0);
	ph.i = -1;
	ph.tm_die = atoi(argv[2]);	
	ph.tm_eat = atoi(argv[3]);
	ph.tm_sleep = atoi(argv[4]);
	ph.tm_p_eat = atoi(argv[6]);
	ph.nbr_philo = atoi(argv[1]);
	ph.nbr_forks = atoi(argv[1]);
	ph.th_philo = malloc ((ph.nbr_philo + 1) * sizeof(pthread_t));
	ph.mutex = malloc((ph.nbr_forks) * sizeof(pthread_mutex_t));
	ph.th_philo[ph.nbr_philo] = 0;
	while(++ph.i < ph.nbr_forks)
		pthread_mutex_init(&ph.mutex[ph.i], NULL);
	ph.i = -1;
	while (++ph.i < ph.nbr_philo)
	{
		pthread_create(&ph.th_philo[ph.i], NULL, &act_philo, &ph);
		pthread_join(ph.th_philo[ph.i], NULL);
	}
	
	
}