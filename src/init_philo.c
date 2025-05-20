#include "philo.h"

int ft_atoi(const char *str)
{
	int num;

	num = 0;
	while (*str >= '0' && *str <= '9') {
		num = num * 10 + (*str - '0');
		str++;
	}
	return num;
}

bool init_resources(t_philo **philos, pthread_t **threads, pthread_mutex_t **forks, int philo_num)
{
	*threads = malloc(sizeof(pthread_t) * philo_num);
	if (!*threads)
		return (false);
	*philos = malloc(sizeof(t_philo) * philo_num);
	if (!*philos)
	{
		free(*threads);
		return (false);
	}
	*forks = malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!*forks)
	{
		free(*threads);
		free(*philos);
		return (false);
	}
	return (true);
}

bool init_data(t_data *data, int philo_num, char **argv, int argc)
{
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->died_mutex, NULL);
	data->is_dead = false;
	data->philo_num = philo_num;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_must_eat = -1;
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	return (true);
}

bool setup_philosophers(t_philo *philos, pthread_mutex_t *forks, t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		philos[i].id = i + 1;
		philos[i].forks = forks;	
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->philo_num;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].num_must_eat = data->num_must_eat;
		philos[i].eat_count = 0;
		philos[i].start_time = get_timestamp();
		philos[i].last_meal_time = get_timestamp();
		philos[i].data = data;
		i++;
	}
	return (true);
}
