#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>

#define NUM_THREADS 5

int ft_atoi(const char *str)
{
	int num = 0;
	while (*str >= '0' && *str <= '9') {
		num = num * 10 + (*str - '0');
		str++;
	}
	return num;
}

long long get_timestamp(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void *philosopher(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		if (philo.id % 2 == 1)
			usleep(200);
		printf("%d is thinking\n", philo.id);
		pthread_mutex_lock(&philo.forks[philo.left_fork]);
		pthread_mutex_lock(&philo.forks[philo.right_fork]);

		printf("%d has taken fork %d\n", philo.id, philo.left_fork);
		usleep(5000);
		pthread_mutex_unlock(&philo.forks[philo.left_fork]);
		pthread_mutex_unlock(&philo.forks[philo.right_fork]);

		printf("%d is sleeping\n", philo.id);
		usleep(5000);
	}
	return NULL;
}

void init_philosopher(t_philo *philo, int id, pthread_mutex_t *forks, int philo_num, char **argv, int argc)
{
	philo->id = id;
	philo->forks = forks;
	philo->left_fork = id - 1;
	philo->right_fork = id % philo_num;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_must_eat = -1;  // -1 means not specified
	if (argc == 6)
		philo->num_must_eat = ft_atoi(argv[5]);
	philo->eat_count = 0;
	philo->last_meal_time = get_timestamp();  // Will be set when simulation starts
}

int main(int argc, char **argv)
{
	int philo_num;
	t_philo *philos;
	pthread_t *threads;
	int i;

	if (argc < 5 || argc > 6)
	{
		printf(ARGV_ERR);
		return (1);
	}

	philo_num = ft_atoi(argv[1]);
	threads = malloc(sizeof(pthread_t) * philo_num);
	philos = malloc(sizeof(t_philo) * philo_num);
	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * philo_num);
	
	i = 0;
	while (i < philo_num) {
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	i = 0;
	while (i < philo_num) {
		init_philosopher(&philos[i], i + 1, forks, philo_num, argv, argc);
		pthread_create(&threads[i], NULL, philosopher, &philos[i]);
		i++;
	}

	i = 0;
	while (i < philo_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(philos);

	return 0;
}