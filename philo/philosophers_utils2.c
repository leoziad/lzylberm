#include "Include/philosophers.h"

void	ft_destroy_mutex(t_philo *philo)
{
	free(philo->params->master_lock);
}

void	ft_one_philo(t_philo *philo)
{
	if (philo->params->philo_nbr == 1)
	{
		ft_print(philo, TOOK_FORK);
		ft_usleep(philo->params->time_to_die, philo);
		ft_philo_kill(philo);
		ft_destroy_mutex(philo);
	}
}

int	ft_get_status(t_philo *philo)
{
	pthread_mutex_lock(philo->params->master_lock);
	if (philo->params->status != ALIVE)
	{
		pthread_mutex_unlock(philo->params->master_lock);
		return (DEAD);
	}
	pthread_mutex_unlock(philo->params->master_lock);
	return (ALIVE);
}

u_int64_t	ft_get_time(void)
{
	static long			start_time = 0;
	long unsigned int	actual_time;
	struct timeval		tv;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		actual_time = 0;
	}
	else
	{
		gettimeofday(&tv, NULL);
		actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time;
	}
	return (actual_time);
}
