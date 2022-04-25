#include "Include/philosophers.h"

static void	ft_check(t_philo *philo, int count_ok, int i)
{
	while (1)
	{
		count_ok = 0;
		i = -1;
		while (++i < philo->params->philo_nbr)
		{
			pthread_mutex_lock(philo[i].params->forks_mutex);
			if (philo[i].meal_count == philo[i].must_eat)
			{
				++count_ok;
				if (count_ok == philo->params->philo_nbr)
				{
					if (ft_philo_check_dead(&philo[i]))
						return ;
					pthread_mutex_unlock(philo[i].params->forks_mutex);
					return ;
				}
			}
			if (ft_philo_check_dead(&philo[i]))
				return ;
			pthread_mutex_unlock(philo[i].params->forks_mutex);
		}
		usleep(7000);
	}	
}

void	*ft_routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo *)philo_void;
	while (ft_get_status(philo) == ALIVE)
	{
		if (philo->meal_count == philo->must_eat)
			return (NULL);
		ft_eat(philo);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		ft_sleep(philo);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		ft_display(philo, THINKING);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		usleep(7000);
	}
	return (NULL);
}

void	ft_execute_philo(t_philo *philo)
{
	int	i;

	i = -1;
	philo->params->time_start = ft_get_time();
	if (ft_init_mutex(philo) == 1)
		return ;
	if (philo->params->philo_nbr == 1)
		return (ft_one_philo(philo));
	while (++i < philo->params->philo_nbr)
	{
		if (i % 2 == 0)
			if (pthread_create(&(philo[i].philo_th), NULL,
					ft_routine, &philo[i]) != 0)
				return ;
	}
	ft_usleep(philo->params->time_to_eat / 10, philo);
	i = -1;
	while (++i < philo->params->philo_nbr)
	{
		if (i % 2 == 1)
			if (pthread_create(&(philo[i].philo_th), NULL,
					ft_routine, &philo[i]) != 0)
				return ;
	}
	ft_check(philo, 0, -1);
}

void	ft_init_thread(t_philo *philo)
{
	int			i;

	i = 0;
	if (!philo)
		return ;
	ft_execute_philo(philo);
	if (philo->params->philo_nbr == 1)
	{
		free(philo);
		return ;
	}
	while (i < philo->params->philo_nbr)
	{
		pthread_join(philo[i].philo_th, NULL);
		i++;
	}
	ft_destroy_mutex(philo);
	if (philo)
		free(philo);
}

int	main(int ac, char **av)
{	
	t_params	*params;
	t_philo		*philo;

	params = malloc(sizeof(t_params));
	if (ac < 5 || ac > 6)
		return (ft_display_error("Nombre d'arguments"));
	if (ft_check_error(av))
	{
		ft_display_error("Mauvais arguments");
		return (1);
	}
	if (ac == 5)
		philo = ft_init_all(&params, av);
	else if (ac == 6)
		philo = ft_init_all2(&params, av);
	if (philo == 0)
	{
		ft_display_error("Mauvaises valeurs d'arguments");
		return (1);
	}
	ft_init_thread(philo);
	free(params);
	return (0);
}
