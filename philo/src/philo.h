/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:10:38 by msawada           #+#    #+#             */
/*   Updated: 2025/05/10 19:10:40 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ARGV_ERR "Usage: ./philo <philosophers> <die> <eat> <sleep> [meals]\n"

typedef struct s_data
{
	pthread_mutex_t	print_mutex;
	bool			is_dead;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				eat_count;
	long long		last_meal_time;
	t_data			*data;
}					t_philo;

long long			get_timestamp(void);
void				print_state(t_philo *philo, t_data *data,
						const char *state);
bool				take_forks(t_philo *philo);
void				update_meal_time(t_philo *philo);
bool				eat(t_philo *philo);
bool				dream(t_philo *philo);
bool				think(t_philo *philo);
void				*philosopher(void *arg);
bool				setup_philosophers(t_philo *philos, pthread_mutex_t *forks,
						t_data *data);
bool				check_death(t_philo *philo, long long current_time);
bool				check_meals(t_philo *philos, int philo_num);
void				*monitor(void *arg);
void				run_threads(pthread_t *threads, t_philo *philos,
						int philo_num);
bool				init_data(t_data *data, int philo_num, char **argv,
						int argc);
bool				init_resources(t_philo **philos, pthread_t **threads,
						pthread_mutex_t **forks, int philo_num);
void				cleanup(t_philo *philos, pthread_t *threads,
						pthread_mutex_t *forks, t_data *data);
int					ft_atoi(const char *str);
bool				check_argv(char **argv);

#endif