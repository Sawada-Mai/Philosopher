#include "philo.h"


void update_meal_time(t_philo *philo)
{
	philo->last_meal_time = get_timestamp();
	philo->eat_count++;
}

bool eat(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is eating");
	update_meal_time(philo);
	usleep(philo->time_to_eat);
	return true;
}

bool dream(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is sleeping");
	usleep(philo->time_to_sleep);
	return true;
}

bool think(t_philo *philo)
{
	if (philo->data->is_dead)
		return false;
	print_state(philo, philo->data, "is thinking");
	return true;
}