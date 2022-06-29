/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:02:18 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 11:57:09 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_var(t_philo *ph, int argc, char **argv)
{
	ph->tm_die = ft_atoi(argv[2]);
	ph->tm_eat = ft_atoi(argv[3]);
	ph->tm_sleep = ft_atoi(argv[4]);
	ph->nbr_philo = ft_atoi(argv[1]);
	ph->tm_p_eat = -1;
	ph->i = -1;
	gettimeofday(&ph->time, NULL);
	if (argc == 6)
		ph->tm_p_eat = ft_atoi(argv[5]);
	if (ph->tm_die == -2 || ph->tm_eat == -2 || ph->tm_sleep == -2
		|| ph->tm_p_eat == -2 || ph->nbr_philo == -2)
		exit(1);
	sem_unlink(FORK);
	sem_unlink(PRINT);
	sem_unlink(DIE);
	ph->th_philo = malloc((ph->nbr_philo) * sizeof(pthread_t));
	ph->fork = sem_open(FORK, O_CREAT, 0664, ph->nbr_philo);
	ph->print = sem_open(PRINT, O_CREAT, 0664, 1);
	ph->die = sem_open(DIE, O_CREAT, 0664, 1);
}

void	create_process(t_philo *ph, int j)
{
	while (++(ph->i) < ph->nbr_philo)
	{
		ph->th_philo[ph->i] = fork();
		if (ph->th_philo[ph->i] == 0)
			philo_process(ph);
	}
	ph->i = -1;
	while (j < ph->nbr_philo)
	{
		if (waitpid(ph->th_philo[++ph->i], NULL, 0) != 0)
			j++;
		if (ph->i == ph->nbr_philo - 1)
			ph->i = -1;
	}
	sem_close(ph->fork);
	sem_close(ph->print);
	sem_close(ph->die);
	sem_unlink(DIE);
	sem_unlink(FORK);
	sem_unlink(PRINT);
}

void	philo_process(t_philo *ph)
{
	int	i;

	i = ph->i;
	if (pthread_create(&ph->th, NULL, &act_sup, ph) != 0)
		exit(1);
	if (pthread_detach(ph->th) != 0)
		exit(1);
	if (ph->tm_p_eat == -1)
	{
		while (1)
			philo_work(ph, i, ph->tm_p_eat);
	}
	else
	{
		while (ph->tm_p_eat > 0)
		{
			philo_work(ph, i, ph->tm_p_eat);
			ph->tm_p_eat--;
		}
	}
	exit(0);
}

void	*act_sup(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
	usleep(300);
	while (1)
	{
		usleep(300);
		if (time_past(ph->die_calcul, ph->end_die) >= ph->tm_die)
		{
			sem_wait(ph->die);
			gettimeofday(&ph->timepast, NULL);
			sem_wait(ph->print);
			printf("%d %d died\n", time_past(ph->time, ph->timepast), ph->i + 1);
			kill(0, SIGINT);
			exit(0);
		}
	}
}
