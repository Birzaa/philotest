#include "philo.h"

int ft_usleep(size_t milliseconds)
{
    size_t start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}

size_t get_current_time(void)
{
    struct timeval time;
    if (gettimeofday(&time, NULL) == -1)
    {
        perror("gettimeofday() error");
        return 0;
    }
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


int	philo_is_ready(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->program->ready);
	ret = philo->program->start;
	pthread_mutex_unlock(&philo->program->ready);
	return (ret);
}

void	wait_threads(t_philo *philo)
{
	while (philo_is_ready(philo) == 0)
		usleep(500);
}

void	ft_usleep2(int time_to, t_philo *philo)
{
	int	pourcent;

	pourcent = 0.1 * time_to;
	while (time_to > 0 && dead_loop(philo) == 0)
	{
		usleep(pourcent);
		time_to -= pourcent;
	}
}

void	ft_usleep3(size_t time, t_philo *p)
{
	long int	current_time;

	current_time = 0;
	current_time = get_current_time();
	while ((get_current_time() - current_time) < time)
	{
		if (dead_loop(p))
			break ;
		if (time > 10000000)
			usleep(time / 100000);
		else
			usleep(time / 10);
	}
}