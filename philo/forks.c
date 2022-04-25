#include "Include/philosophers.h"

void	ft_philo_kill(t_philo *philo)
{
	u_int64_t	time;	

	time = ft_get_time() - philo->params->time_start;
	pthread_mutex_lock(&philo->lock);
	printf("%lu\t", time);
	printf("%d is dead\n", philo->position + 1);
	philo->params->status = DEAD;
	pthread_mutex_unlock(&philo->lock);
}

int	ft_philo_check_dead(t_philo *philo)
{
	if ((ft_get_time() - philo->last_meal)
		>= ((u_int64_t)philo->params->time_to_die))
	{
		ft_philo_kill(philo);
		pthread_mutex_unlock(philo->params->forks_mutex);
		return (1);
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	ft_display(philo, SLEEPING);
	ft_usleep(philo->params->time_to_sleep, philo);
}

int	ft_forks(t_philo *philo)
{
	if (philo->position % 2 == 0)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_display(philo, TOOK_FORK);
	if (philo->position % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork))
		{
			pthread_mutex_unlock(&philo->right_fork);
			return (1);
		}
		ft_display(philo, TOOK_FORK);
	}
	else
	{
		if (pthread_mutex_lock(&philo->right_fork))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		ft_display(philo, TOOK_FORK);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{	
	if (ft_forks(philo) == 1)
		return (1);
	ft_display(philo, EATING);
	pthread_mutex_lock(philo->params->forks_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->params->forks_mutex);
	ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_lock(philo->params->forks_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(philo->params->forks_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (0);
}
