/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   philo_bonus.c                                     :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: akhouya <akhouya@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2022/06/25 17:37:16 by akhouya         #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/06/25 17:37:16 by akhouya      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include "philo_bonus.h"


void	 msleep(int sleep)
{
	int past;
	struct timeval before;
	struct timeval after;
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

int time_past(struct timeval before, struct timeval after)
{
	int r;
	int past;

    gettimeofday(&after, NULL);
	past = after.tv_sec * 1000 + after.tv_usec / 1000;
	r = before.tv_sec * 1000 + before.tv_usec / 1000;
	r = past - r;
	return (r);
}

void    philo_work(t_philo *ph, int i, int j)
{
    sem_wait(ph->fork);
    sem_wait(ph->print);
    printf("%d %d has taken fork\n", time_past(ph->time, ph->timepast), i + 1);
    sem_post(ph->print);
    sem_wait(ph->fork);
    sem_wait(ph->print);
    printf("%d %d has taken fork\n", time_past(ph->time, ph->timepast), i + 1);
    sem_post(ph->print);
    sem_wait(ph->print);
    printf("%d %d is eating\n", time_past(ph->time, ph->timepast), i + 1);
    sem_post(ph->print);
    gettimeofday(&ph->die_calcul, NULL);
    msleep(ph->tm_eat);
    sem_post(ph->fork);
    sem_post(ph->fork);
    if(j == 1)
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
int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
    t_philo *ph;
    int j;

    j = 0;
    ph = malloc(sizeof(t_philo));
    if (!ph)
		return (1);
	ph->tm_die = ft_atoi(argv[2]);
	ph->tm_eat = ft_atoi(argv[3]);
	ph->tm_sleep = ft_atoi(argv[4]);
	ph->nbr_philo = ft_atoi(argv[1]);
	ph->tm_p_eat = -1;
    ph->i = -1;
    gettimeofday(&ph->time, NULL);
	if (argc == 6)
		ph->tm_p_eat = ft_atoi(argv[5]);
	if (ph->tm_die == -2 || ph->tm_eat == -2 || ph->tm_sleep == -2 || ph->tm_p_eat == -2 || ph->nbr_philo == -2)
		return 1;
    sem_unlink(FORK);
    sem_unlink(PRINT);
    sem_unlink(DIE);
    ph->th_philo = malloc((ph->nbr_philo) * sizeof(pthread_t));
    ph->fork = sem_open(FORK, O_CREAT, 0664, ph->nbr_philo);
    ph->print = sem_open(PRINT, O_CREAT, 0664, 1);
    ph->die = sem_open(DIE, O_CREAT, 0664, 1);
    while (++(ph->i) < ph->nbr_philo)
    {
        ph->th_philo[ph->i] = fork();
        if (ph->th_philo[ph->i] == 0)
            philo_process(ph);
    }
    ph->i = -1;
    while(j < ph->nbr_philo)
    {
        if(waitpid(ph->th_philo[++ph->i], NULL, 0) != 0)
            j++;
        if(ph->i == ph->nbr_philo - 1)
            ph->i = -1;
    }
    sem_close(ph->fork);
    sem_close(ph->print);
    sem_close(ph->die);
    sem_unlink(DIE);
    sem_unlink(FORK);
    sem_unlink(PRINT);
}

void*   act_sup(void *th)
{
    t_philo *ph;

    ph = (t_philo*)th;
    usleep(300);
    while(1)
    {
        usleep(300);
        if (time_past(ph->die_calcul, ph->end_die) >= ph->tm_die)
		{
            sem_wait(ph->die);
			gettimeofday(&ph->timepast, NULL);
			sem_post(ph->print);
			sem_wait(ph->print);
			printf("%d %d died\n", time_past(ph->time, ph->timepast), ph->i + 1);
            kill(0, SIGINT);
			exit(0);
		}
        
    }
}
void philo_process(t_philo *ph)
{
    int i;

    i = ph->i;
    // usleep(200);
    if(pthread_create(&ph->th, NULL, &act_sup, ph) != 0)
        exit(1);
    if (pthread_detach(ph->th) != 0)
        exit(1);
    if (ph->tm_p_eat == -1)
    {
        while(1)
            philo_work(ph, i, ph->tm_p_eat);
    }
    else
    {
        while(ph->tm_p_eat > 0)
        {
            philo_work(ph, i, ph->tm_p_eat);
            ph->tm_p_eat--;
        }
    }
    exit(0);
}