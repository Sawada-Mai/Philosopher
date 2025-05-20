#include "philo.h"

void cleanup(t_philo *philos, pthread_t *threads, pthread_mutex_t *forks, t_data *data)
{
	int i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died_mutex);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	free(forks);
	free(threads);
	free(philos);
}


void ft_usleep(long long time)
{
	long long start = get_timestamp();

	while ((get_timestamp() - start) < time)
		usleep(250);
}


void print_state(t_philo *philo, t_data *data, const char *state)
{
	long long	time;

	pthread_mutex_lock(&data->print_mutex);
	time = get_timestamp() - philo->start_time;
	printf("%lld %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&data->print_mutex);
}


long long get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


int main(int argc, char **argv)
{
	int philo_num;
	t_philo *philos;
	pthread_t *threads;
	pthread_mutex_t *forks;
	t_data data;

	if (argc != 5 && argc != 6)
		return (printf(ARGV_ERR), 1);
	if (!check_argv(argv))
		return (printf(ARGV_NUM_ERR), 1);
	philo_num = ft_atoi(argv[1]);
	if (!init_resources(&philos, &threads, &forks, philo_num))
		return (1);
	if (!init_data(&data, philo_num, argv, argc))
		return (1);
	setup_philosophers(philos, forks, &data);
	run_threads(threads, philos, philo_num);
	cleanup(philos, threads, forks, &data);
	return (0);
}
