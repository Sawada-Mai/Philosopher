#include "philo.h"

bool take_forks(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	print_state(philo, philo->data, "has taken a fork");

	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	print_state(philo, philo->data, "has taken a fork");

	return true;
}


void update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

bool eat(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is eating");
	update_meal_time(philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	return true;
}

bool dream(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	return true;
}

bool think(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is thinking");
	return true;
}