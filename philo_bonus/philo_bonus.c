/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:49:40 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 12:19:51 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	gettimeofday(&after, NULL);
	past = after.tv_sec * 1000 + after.tv_usec / 1000;
	r = before.tv_sec * 1000 + before.tv_usec / 1000;
	r = past - r;
	return (r);
}

void	p_philo_fork(t_philo *ph, int i)
{
	sem_wait(ph->fork);
	sem_wait(ph->print);
	printf("%d %d has taken fork\n", time_past(ph->time, ph->timepast), i + 1);
	sem_post(ph->print);
	sem_wait(ph->fork);
	sem_wait(ph->print);
	printf("%d %d has taken fork\n", time_past(ph->time, ph->timepast), i + 1);
	sem_post(ph->print);
}

void	philo_work(t_philo *ph, int i, int j)
{
	p_philo_fork(ph, i);
	sem_wait(ph->print);
	printf("%d %d is eating\n", time_past(ph->time, ph->timepast), i + 1);
	sem_post(ph->print);
	gettimeofday(&ph->die_calcul, NULL);
	msleep(ph->tm_eat);
	sem_post(ph->fork);
	sem_post(ph->fork);
	if (j == 1)
		exit(0);
	sem_wait(ph->print);
	printf("%d %d is sleeping\n", time_past(ph->time, ph->timepast), i + 1);
	sem_post(ph->print);
	msleep(ph->tm_sleep);
	sem_wait(ph->print);
	printf("%d %d is thinking\n", time_past(ph->time, ph->timepast), i + 1);
	sem_post(ph->print);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	int		j;

	if (argc != 5 && argc != 6)
		return (1);
	j = 0;
	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (1);
	init_var(ph, argc, argv);
	create_process(ph, j);
}
