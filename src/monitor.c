
#include "philo.h"

bool check_death(t_philo *philo, long long current_time)
{
	if (current_time - philo->last_meal_time > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (!philo->data->is_dead)
		{
			philo->data->is_dead = true;
			printf("%lld %d died\n", current_time, philo->id);
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (true);
	}
	return (false);
}

bool check_meals(t_philo *philos, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].num_must_eat != -1 && philos[i].eat_count < philos[i].num_must_eat)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return false;
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return true;
}


void *monitor(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	int i;
	long long current_time;

	while (1)
	{
		i = 0;
		while (i < philos[0].data->philo_num)
		{
			current_time = get_timestamp();
			if (check_death(&philos[i], current_time))
				return (NULL);
			i++;
		}
		if (philos[0].num_must_eat != -1 && check_meals(philos, philos[0].data->philo_num))
		{
			pthread_mutex_lock(&philos[0].data->print_mutex);
			philos[0].data->is_dead = true;
			pthread_mutex_unlock(&philos[0].data->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}