/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:30:45 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/29 10:31:53 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdatomic.h>

typedef struct s_philo
{
	pthread_t			*th_philo;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		mutex_print;
	int					tm_die;	
	int					tm_eat;
	int					tm_sleep;
	int					tm_p_eat;
	int					nbr_philo;
	atomic_int			i;
	atomic_int			end;
	struct timeval		time;
	struct timeval		timepast;
	struct timeval		*die_calcul;
	struct timeval		*end_die;
	atomic_int			die;
}	t_philo;
void	msleep(int sleep);
int		time_past(struct timeval before, struct timeval after);
void	mutex_destroy_forks(t_philo *ph);
void	destroy_mutex(t_philo *ph);
void	thread(t_philo *p, int i, int fork, int j);
void	*act_philo(void *ph);
int		ft_atoi(const char *nptr);
int		init_var(t_philo *ph, char **argv, int argc);
int		calcule(const char *nptr, int sign);
void	condition_act(t_philo *p, int i, int j);
void	tphilo_take_forks(t_philo *p, int i, int fork);
#endif