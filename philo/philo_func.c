/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   philo_func.c                                      :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: akhouya <akhouya@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2022/06/24 10:45:07 by akhouya         #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/06/24 10:45:07 by akhouya      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include "philo.h"

void    mutex_destroy_forks(t_philo *ph)
{
    int j;
    j = -1;
    while(++j < ph->i)
		pthread_mutex_destroy(&ph->mutex[j]);
}
void    destroy_mutex(t_philo *ph)
{
    int j;
    j = -1;
    pthread_mutex_destroy(&ph->mutex_print);
	while(++j < ph->i)
		pthread_mutex_destroy(&ph->mutex[j]);
}

void    thread(t_philo *p, int i, int fork, int j)
{
    // usleep(100);
    pthread_mutex_lock(&p->mutex[i]);
    pthread_mutex_lock(&p->mutex_print);
    printf("%d %d has taken fork\n", time_past(p->time, p->timepast), i + 1);
    pthread_mutex_unlock(&p->mutex_print);

    pthread_mutex_lock(&p->mutex[fork]);

    pthread_mutex_lock(&p->mutex_print);
    printf("%d %d has taken fork\n", time_past(p->time, p->timepast), i + 1);
    pthread_mutex_unlock(&p->mutex_print);

    pthread_mutex_lock(&p->mutex_print);
    printf("%d %d is eating\n", time_past(p->time, p->timepast), i + 1);
    pthread_mutex_unlock(&p->mutex_print);
    gettimeofday(&p->die_calcul[i], NULL);
    msleep(p->tm_eat);
    
    ;
    pthread_mutex_unlock(&p->mutex[fork]);
    pthread_mutex_unlock(&p->mutex[i]);
    if(j == 1)
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

void*   act_philo(void *ph)
{
    t_philo *p;
    int i;
    int j;
    int fork;

    p = (t_philo*) ph;
    i = p->i;
    j = p->tm_p_eat;
    if (j == -1)
    {
        while(1)
        {
            fork = i + 1;
            if( fork > p->nbr_philo - 1)
                fork = 0;
            thread(p, i, fork, j);
        }
    }
    else
    {
         while(j > 0)
        {
            fork = i + 1;
            if( fork > p->nbr_philo - 1)
                fork = 0;
            thread(p, i, fork, j);
            j--;
        }
        p->end++;
    }
   
    return 0;
}