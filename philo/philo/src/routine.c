#include "philo.h"


void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", get_current_time() - philo->program->start_time, philo->id,
		status);
	pthread_mutex_unlock(philo->write_lock);
}

void	pick_up_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (dead_loop(philo))
		return ;
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->l_fork);
	if (dead_loop(philo))
		return ;
	print_status(philo, "has taken a fork");
}

void	pick_up_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	if (dead_loop(philo))
		return ;
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	if (dead_loop(philo))
		return ;
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (dead_loop(philo))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->meal_lock);
		return ;
	}
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	philo->eating = 1;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);

	ft_usleep2(philo->time_to_eat, philo);

	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	if (!philo->program->stop)
	{
		print_status(philo, "is thinking");
		ft_usleep2(philo->t_think, philo);
	}
}

void	ft_slip(t_philo *philo)
{
	if (!philo->program->stop)
	{
		print_status(philo, "is sleeping");
		ft_usleep2(philo->time_to_sleep, philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->program->m_time);
	philo->program->start_time = get_current_time();
	pthread_mutex_unlock(&philo->program->m_time);
	if(philo->program->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep2(philo->time_to_die, philo);
		print_status(philo, "died");
		return NULL;
	}
	wait_threads(philo);
	usleep(100);
	if (philo->id % 2 == 0)
		ft_usleep2(philo->time_to_eat, philo);
	while (!dead_loop(philo))
	{
		if (philo->id % 2 == 1)
			pick_up_forks_odd(philo);
		else
			pick_up_forks_even(philo);
		eat(philo);
		ft_slip(philo);
		think(philo);
	}
	return (NULL);
}