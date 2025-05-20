#include "philo.h"


bool is_dead(t_data *data)
{
	bool dead;

	pthread_mutex_lock(&data->died_mutex);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->died_mutex);
	return (dead);
}


void update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	print_state(philo, philo->data, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	print_state(philo, philo->data, "has taken a fork");

	print_state(philo, philo->data, "is eating");
	update_meal_time(philo);
	ft_usleep(philo->time_to_eat);

	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
}


void dream(t_philo *philo)
{
	print_state(philo, philo->data, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void think(t_philo *philo)
{
	print_state(philo, philo->data, "is thinking");
}