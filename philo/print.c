#include "Include/philosophers.h"

int	ft_print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

int	ft_print_message(t_philo *philo, char c)
{
	if (c == TOOK_FORK)
		printf("%d has taken a fork\n", philo->position + 1);
	else if (c == EATING)
		printf("%d is eating\n", philo->position + 1);
	else if (c == SLEEPING)
		printf("%d is sleeping\n", philo->position + 1);
	else if (c == THINKING)
		printf("%d is thinking\n", philo->position + 1);
	else if (c == DEAD)
	{
		printf("%d is dead\n", philo->position + 1);
		return (1);
	}
	return (0);
}

void	ft_print(t_philo *philo, char c)
{
	u_int64_t	time;	

	pthread_mutex_lock(philo->params->master_lock);
	if (philo->params->status == DEAD)
	{
		pthread_mutex_unlock(philo->params->master_lock);
		return ;
	}
	time = ft_get_time() - philo->params->time_start;
	printf("%lu\t", time);
	ft_print_message(philo, c);
	pthread_mutex_unlock(philo->params->master_lock);
}
