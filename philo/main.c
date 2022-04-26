#include "Include/philosophers.h"

static void	ft_monitor(t_philo *philo, int count_ok, int i)
{
	while (1)
	{
		count_ok = 0;
		i = -1;
		while (++i < philo->params->philo_nbr)
		{
			pthread_mutex_lock(philo[i].params->master_lock);
			if (philo[i].eat_count == philo[i].must_eat)
			{
				++count_ok;
				if (count_ok == philo->params->philo_nbr)
				{
					if (ft_check_death(&philo[i]))
						return ;
					pthread_mutex_unlock(philo[i].params->master_lock);
					return ;
				}
			}
			if (ft_check_death(&philo[i]))
				return ;
			pthread_mutex_unlock(philo[i].params->master_lock);
		}
		usleep(7000);
	}	
}

void	*ft_routine(void *philo_ptr)
{
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	while (ft_get_status(philo) == ALIVE)
	{
		if (philo->eat_count == philo->must_eat)
			return (NULL);
		ft_eat(philo);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		ft_sleep(philo);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		ft_print(philo, THINKING);
		if (ft_get_status(philo) != ALIVE)
			return (NULL);
		usleep(7000);
	}
	return (NULL);
}

void	ft_create_philo(t_philo *philo)
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
	ft_monitor(philo, 0, -1);
}

void	ft_init_thread(t_philo *philo)
{
	int		i;

	i = 0;
	if (!philo)
		return ;
	ft_create_philo(philo);
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

int	main(int argc, char **argv)
{	
	t_params	*params;
	t_philo		*philo;

	params = malloc(sizeof(t_params));
	if (argc < 5 || argc > 6)
		return (ft_print_error("Incorrect number of arguments"));
	if (ft_check_error(argv))
	{
		ft_print_error("Bad arguments");
		return (1);
	}
	if (argc == 5)
		philo = ft_init_all(&params, argv);
	else if (argc == 6)
		philo = ft_init_all2(&params, argv);
	if (!philo)
	{
		ft_print_error("Bad arguments");
		return (1);
	}
	ft_init_thread(philo);
	free(params);
	return (0);
}
