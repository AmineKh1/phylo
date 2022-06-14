#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.c>

#include <sys/time.h>
#include <pthread.h>

void*	

int	main(int argc, char **argv)
{
	if ( argc != 5 || atoi(argv[1]) < 1)
		perror("Error\n");
	pthread_t th_phylo[atoi(argv[1])];
	int tm_die;	
	int tm_eat;
	int tm_sleep;
	int tm_p_eat;

	tm_die = atoi(argv[2]);	
	tm_eat = atoi(argv[3]);
	tm_sleep = atoi(argv[4]);
	tm_p_eat = atoi(argv[6]);

}