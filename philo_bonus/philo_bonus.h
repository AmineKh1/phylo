/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   philo_bonus.h                                     :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: akhouya <akhouya@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2022/06/25 17:37:55 by akhouya         #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/06/25 17:37:55 by akhouya      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdatomic.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# define FORK "fork"
# define PRINT "print"
# define DIE "die"
# include <signal.h>
typedef struct s_philo
{
    pid_t   *th_philo;
	pthread_t th;;
	int tm_die;	
	int tm_eat;
	int tm_sleep;
	int tm_p_eat;
	int nbr_philo;
	sem_t *fork;
	sem_t *print;
	sem_t *die;
	atomic_int i;
    struct timeval  time;
	struct timeval  timepast;
	struct timeval	end_die;
	struct timeval	die_calcul;
}       t_philo;
int time_past(struct timeval before, struct timeval after);
void	 msleep(int sleep);
void    philo_work(t_philo *p, int i, int j);
void philo_process(t_philo *ph);
void*   act_sup(void *th);
int	ft_atoi(const char *nptr);
#endif