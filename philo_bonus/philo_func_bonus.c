/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   philo_func_bonus.c                                :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: akhouya <akhouya@student.1337.ma>             +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2022/06/26 03:01:09 by akhouya         #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2022/06/26 03:01:09 by akhouya      ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include "philo_bonus.h"

// void*   act_philo(void *ph)
// {
//     t_philo *p;
//     int i;
//     int j;
//     int fork;

//     p = (t_philo*) ph;
//     i = p->i;
//     j = p->tm_p_eat;
//     if (j == -1)
//     {
//         while(1)
//         {
//             fork = i + 1;
//             if( fork > p->nbr_philo - 1)
//                 fork = 0;
//             thread(p, i, fork, j);
//         }
//     }
//     else
//     {
//          while(j > 0)
//         {
//             fork = i + 1;
//             if( fork > p->nbr_philo - 1)
//                 fork = 0;
//             thread(p, i, fork, j);
//             j--;
//         }
//         p->end++;
//     }
   
//     return 0;
// }

static int	calcule(const char *nptr, int sign)
{
	unsigned long	r;

	r = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		r = r * 10;
		r = r + (*nptr - '0');
		nptr++;
	}
	if ((r > 2147483647 && sign == 1) || (r > 2147483648 && sign == -1))
		return (-2);
	return ((int)r * sign);
}

int	ft_atoi(const char *nptr)
{
	unsigned long	r;
	int				signe;

	r = 0;
	signe = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\r'
		|| *nptr == '\n' || *nptr == '\f')
		nptr++;
	if (*nptr == '-')
	{
		return (-2);
	}
	else if (*nptr == '+')
		return (-2);
	r = calcule(nptr, signe);
	return (r);
}
