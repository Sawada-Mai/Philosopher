#include "philo.h"

void *philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!is_dead(philo->data))
	{
		eat(philo);
		if (philo->num_must_eat != -1 && philo->eat_count >= philo->num_must_eat)
    	break;
		dream(philo);
		think(philo);
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
