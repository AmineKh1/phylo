/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:16:12 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 10:26:00 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tphilo_take_forks(t_philo *p, int i, int fork)
{
	pthread_mutex_lock(&p->mutex[i]);
	pthread_mutex_lock(&p->mutex_print);
	printf("%d %d has taken fork\n", time_past(p->time, p->timepast), i + 1);
	pthread_mutex_unlock(&p->mutex_print);
	pthread_mutex_lock(&p->mutex[fork]);
	pthread_mutex_lock(&p->mutex_print);
	printf("%d %d has taken fork\n", time_past(p->time, p->timepast), i + 1);
	pthread_mutex_unlock(&p->mutex_print);
}

void	thread(t_philo *p, int i, int fork, int j)
{
	tphilo_take_forks(p, i, fork);
	pthread_mutex_lock(&p->mutex_print);
	printf("%d %d is eating\n", time_past(p->time, p->timepast), i + 1);
	pthread_mutex_unlock(&p->mutex_print);
	gettimeofday(&p->die_calcul[i], NULL);
	msleep(p->tm_eat);
	pthread_mutex_unlock(&p->mutex[fork]);
	pthread_mutex_unlock(&p->mutex[i]);
	if (j == 1)
		return ;
	pthread_mutex_lock(&p->mutex_print);
	gettimeofday(&p->timepast, NULL);
	printf("%d %d is sleeping\n", time_past(p->time, p->timepast), i + 1);
	pthread_mutex_unlock(&p->mutex_print);
	msleep(p->tm_sleep);
	pthread_mutex_lock(&p->mutex_print);
	gettimeofday(&p->timepast, NULL);
	printf("%d %d is thinking\n", time_past(p->time, p->timepast), i + 1);
	pthread_mutex_unlock(&p->mutex_print);
}

void	condition_act(t_philo *p, int i, int j)
{
	int	fork;

	if (j == -1)
	{
		while (1)
		{
			fork = i + 1;
			if (fork > p->nbr_philo - 1)
				fork = 0;
			thread(p, i, fork, j);
		}
	}
	else
	{
		while (j > 0)
		{
			fork = i + 1;
			if (fork > p->nbr_philo - 1)
				fork = 0;
			thread(p, i, fork, j);
			j--;
		}
		p->end++;
	}
}

void	*act_philo(void *ph)
{
	t_philo	*p;
	int		i;
	int		j;

	p = (t_philo *) ph;
	i = p->i;
	j = p->tm_p_eat;
	condition_act(p, i, j);
	return (0);
}

int	calcule(const char *nptr, int sign)
{
	unsigned long	r;

	r = 0;
	if (*nptr < '0' || *nptr > '9')
		return (-2);
	while (*nptr >= '0' && *nptr <= '9')
	{
		r = r * 10;
		r = r + (*nptr - '0');
		nptr++;
	}
	if ((*nptr < '0' || *nptr > '9') && *nptr != '\0')
		return (-2);
	if ((r > 2147483647 && sign == 1) || (r > 2147483648 && sign == -1))
		return (-2);
	return ((int)r * sign);
}
