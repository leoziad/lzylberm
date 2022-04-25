#include "Include/philosophers.h"

int	ft_check_error(char **av)
{
	if (ft_is_digit(av[1]) == 0 || ft_is_digit(av[2]) == 0
		|| ft_is_digit(av[3]) == 0 || ft_is_digit(av[4]) == 0)
	{
		return (1);
	}
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[2]) == -1 || ft_atoi(av[3]) == -1
		|| ft_atoi(av[4]) == -1)
		return (1);
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) < 60)
		return (1);
	if (av[5])
	{
		if (!ft_is_digit(av[5]))
			return (1);
		if (ft_atoi(av[5]) == 0)
			return (1);
		if (ft_atoi(av[5]) == -1)
			return (1);
	}
	return (0);
}
