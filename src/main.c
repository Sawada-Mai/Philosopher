/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:39:11 by msawada           #+#    #+#             */
/*   Updated: 2025/03/27 19:57:15 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_argv(char *argv)
{
	
}

int ft_putstr_fd(char *str, int fd)
{
	if (fd < 0 || fd > 1024)
		return (1);
	if (str == NULL)
		return (1);
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
	return (fd);
}

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd(ARGV_ERR, 2));
	if (check_argv(argv))
		return (ft_putstr_fd(ARGV_ERR, 2));
	// init_philo(argc, argv);
	return (0);
}