#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

enum	status{
DEAD = 0,
ALIVE,
TOOK_FORK,
EATING,
SLEEPING,
THINKING,
};

typedef struct s_philo
{
	pthread_t		philo_th;
	int				position;
	int				is_eating;
	int				must_eat;
	int				eat_count;
	int				status;
	u_int64_t		last_eat;
	u_int64_t		time_limit;
	struct s_params	*params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	ft_display;
}					t_philo;


typedef struct s_params
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_nbr;
	int				status;
	u_int64_t		time_start;
	t_philo			*philo;
	pthread_mutex_t	*master_lock;
}	t_params;

t_philo		*ft_init_all(t_params **start, char **av);
t_philo		*ft_init_all2(t_params **start, char **av);
int			ft_print_error(char *str);
int			ft_atoi(char *str);
size_t		ft_strlen(char *str);
int			ft_is_digit(char *str);
int			ft_forks(t_philo *philo);
int			ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_drop_forks(t_philo *philo);
void		ft_print(t_philo *philo, char c);
u_int64_t	ft_get_time(void);
void		ft_usleep2(size_t	time, t_params *ph);
int			ft_check_error(char **av);
int			ft_must_eat(t_params *start, char **av);
int			ft_must_eat2(t_params *start);
int			ft_is_int(t_params *start);
int			ft_init_mutex(t_philo *philo);
int			ft_check_death(t_philo *philo);
void		ft_destroy_mutex(t_philo *philo);
void		ft_usleep(long unsigned int time_in_ms, t_philo *philo);
int			ft_get_status(t_philo *philo);
void		ft_one_philo(t_philo *philo);
void		ft_philo_kill(t_philo *philo);

#endif
