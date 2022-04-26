#include "Include/philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_check_number_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	if (ft_check_number_size(str))
		return (-1);
	result = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_usleep(long unsigned int time_in_ms, t_philo *philo)
{
	unsigned long	start;

	start = ft_get_time();
	while (1)
	{
		if (ft_get_time() - start >= time_in_ms)
			break;
		usleep(philo->params->philo_nbr * 2);
	}
}
