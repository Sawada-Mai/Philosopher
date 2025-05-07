#include "philo.h"

void print_take_fork(t_philo *philo, int fork_id)
{
	print_state(philo, philo->data, "has taken a fork");
}

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

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
}