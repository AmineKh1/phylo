/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:01:20 by akhouya           #+#    #+#             */
/*   Updated: 2022/06/15 13:56:50 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHiLO_H
# define PHiLO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
typedef struct s_philo
{
    pthread_t *th_philo;
    pthread_mutex_t *mutex;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_incre;
	pthread_mutex_t mutex_eat;
	pthread_mutex_t mutex_timeup;
	pthread_mutex_t end_mutex;
	int				*philo_eat;
	pthread_t supv;
	int tm_die;	
	int tm_eat;
	int tm_sleep;
	int tm_p_eat;
	int nbr_philo;
	int nbr_forks;
	int i;
	int ms_past;
	int end;
	int time_past;
    struct timeval  time;
	struct timeval  timepast;
	struct timeval  *die_calcul;
	struct timeval  *end_die;
	int increment;
	int die;
}       t_philo;
int	time_past(t_philo *ph);
int	msleep(t_philo *ph, int sleep);
void*	act_philo(void *ph);
int	time_past_bonus(t_philo *ph);
#endif