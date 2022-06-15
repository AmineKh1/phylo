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
typedef struct s_philo
{
    pthread_t *th_philo;
    pthread_mutex_t *mutex;
	int tm_die;	
	int tm_eat;
	int tm_sleep;
	int tm_p_eat;
	int nbr_philo;
	int nbr_forks;
	int i;
    struct timeval  time;
}       t_philo;



#endif