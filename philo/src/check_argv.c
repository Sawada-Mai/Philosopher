/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:10:24 by msawada           #+#    #+#             */
/*   Updated: 2025/05/10 19:10:25 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			printf("Non-numeric arguments are mixed in\n");
			return (false);
		}
		str++;
	}
	return (true);
}

bool	check_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_num(argv[i]))
			return (false);
		i++;
	}
	return (true);
}
