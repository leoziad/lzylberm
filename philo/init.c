#include "Include/philosophers.h"

int	ft_init_mutex(t_philo *philo)
{
	philo->params->master_lock = malloc(sizeof(pthread_mutex_t));
	if (!philo->params->master_lock)
		return (1);
	pthread_mutex_init(philo->params->master_lock, NULL);
	return (0);
}

void	ft_init_params(t_params *params, char **av)
{
	params->philo_nbr = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	params->status = ALIVE;
}

t_philo	*ft_init_all(t_params **params, char **av)
{
	t_philo		*philo;
	int			i;

	i = 0;
	ft_init_params(*params, av);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	if (!philo)
		return (NULL);
	while (i < ft_atoi(av[1]))
	{
		philo[i].params = *params;
		philo[i].position = i;
		philo[i].must_eat = -1;
		philo[i].eat_count = 0;
		philo[i].last_eat = 0;
		philo[i].status = ALIVE;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		philo[(i + 1) % philo->params->philo_nbr].left_fork
			= &philo[i].right_fork;
		i++;
	}
	return (philo);
}

t_philo	*ft_init_all2(t_params **params, char **av)
{
	t_philo		*philo;
	int			i;

	i = 0;
	ft_init_params(*params, av);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	if (!philo)
		return (NULL);
	while (i < ft_atoi(av[1]))
	{
		philo[i].params = *params;
		philo[i].position = i;
		philo[i].eat_count = 0;
		philo[i].last_eat = 0;
		philo[i].status = ALIVE;
		philo[i].must_eat = ft_atoi(av[5]);
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&philo[i].right_fork, NULL);
		philo[(i + 1) % philo->params->philo_nbr].left_fork
			= &philo[i].right_fork;
			i++;
	}
	return (philo);
}
