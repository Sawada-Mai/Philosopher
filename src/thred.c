#include "philo.h"

void *philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->is_dead)
			break;
		if (philo->id % 2 == 1)
			usleep(1000);
		if (!take_forks(philo))
			break;
		if (!eat(philo))
			break;
		if (philo->num_must_eat != -1 && philo->eat_count >= philo->num_must_eat)
    	break;
		if (philo->data->is_dead)
			break;
		if (!dream(philo))
			break;
		if (!think(philo))
			break;
	}
	return NULL;
}

void run_threads(pthread_t *threads, t_philo *philos, int philo_num)
{
	int i;
	pthread_t monitor_thread;

	i = 0;
	while (i < philo_num)
	{
		pthread_create(&threads[i], NULL, philosopher, &philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, philos);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < philo_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
