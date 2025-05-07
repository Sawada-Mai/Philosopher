#include "philo.h"

void cleanup(t_philo *philos, pthread_t *threads, pthread_mutex_t *forks, t_data *data)
{
	pthread_mutex_destroy(&data->print_mutex);
	free(forks);
	free(threads);
	free(philos);
}

long long get_timestamp(void)
{
	static long long	start_time = 0;
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start_time == 0)
		start_time = ms;
	return (ms - start_time);
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
		return (1);
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
