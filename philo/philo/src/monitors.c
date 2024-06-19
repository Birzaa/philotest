#include "philo.h"


int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	int dead_status = philo->program->stop;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (dead_status);
}

int	check_philo_death(t_philo *philo, t_program *program, size_t time_to_die)
{

	pthread_mutex_lock(&philo->program->dead_lock);
	int died = 0;
	if (get_current_time() - philo->last_meal >= time_to_die / 1000
		&& philo->eating == 0)
	{
		program->dead_flag = 1;
		philo->dead = 1;
		philo->program->stop = 1;
		print_status(philo, "died");
		died = 1;
	}

	pthread_mutex_unlock(&philo->program->dead_lock);

	return (died);
}

int	check_all_philos_ate(t_program *program)
{
	int all_ate = 1;
	int i = 0;

	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->philos[i].meal_lock);
		if (program->philos[i].meals_eaten < program->nb_must_eat)
		{
			all_ate = 0;
			pthread_mutex_unlock(&program->philos[i].meal_lock);
			break ;
		}
		pthread_mutex_unlock(&program->philos[i].meal_lock);
		i++;
	}
	return (all_ate);
}

void	*monitor(void *arg)
{
	t_program *program = (t_program *)arg;
	wait_threads(program->philos);
	while (1)
	{
		int i = 0;
		while (i < program->num_philos)
		{
			if (check_philo_death(&program->philos[i], program,
					program->philos[i].time_to_die))
				break ;
			i++;
		}
		if (program->stop == 1)
			break ;
		if (program->nb_must_eat != -1)
		{
			if (check_all_philos_ate(program))
			{
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = 1;
				program->stop = 1;
				pthread_mutex_unlock(&program->dead_lock);
			}
			if (program->stop == 1)
				break ;
		}
	}
	return (NULL);
}
