/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawadamai <sawadamai@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:42:07 by msawada           #+#    #+#             */
/*   Updated: 2025/05/04 11:51:40 by sawadamai        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>



#	define ARGV_ERR "Usage: ./philo <philosophers> <die> <eat> <sleep> [meals]\n"


typedef struct s_philo {
	int id;
	int left_fork;
	int right_fork;
	pthread_mutex_t *forks;
	int time_to_die;    // time in milliseconds
	int time_to_eat;    // time in milliseconds
	int time_to_sleep;  // time in milliseconds
	int num_must_eat;   // number of times each philosopher must eat (optional)
	int eat_count;      // count of how many times this philosopher has eaten
	long long last_meal_time;  // timestamp of last meal
} t_philo;



#endif