#include "philo.h"

bool is_num(char *str)
{
	while(*str)
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

bool check_argv(char **argv)
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if(!is_num(argv[i]))
			return (false);
		i++;
	}
	return (true);
}