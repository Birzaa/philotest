#include "philo.h"

void init_global_mutexes(t_program *program) 
{
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->check_eat, NULL);
    pthread_mutex_init(&program->ready, NULL);
    pthread_mutex_init(&program->mutex_begin, NULL);
    pthread_mutex_init(&program->m_time, NULL);
    pthread_mutex_init(&program->test, NULL);
}

void init_philosophers(t_program *program, int num_philos, size_t time_to_die, size_t time_to_eat, size_t time_to_sleep)
{
    program->philos = malloc(num_philos * sizeof(t_philo));
    int i = 0;
    program->stop = 0;
    while (i < num_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].eating = 0;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = get_current_time();
        program->philos[i].last_meal2 = get_current_time();
        program->philos[i].time_to_die = time_to_die;
        program->philos[i].time_to_eat = time_to_eat;
        program->philos[i].time_to_sleep = time_to_sleep;
        program->philos[i].num_times_to_eat = -1; 
        program->philos[i].dead = program->dead_flag;
		program->philos[i].r_fork = NULL;
        pthread_mutex_init(&program->philos[i].last_meal_lock, NULL);
        if (program->philos[i].time_to_eat > program->philos[i].time_to_sleep)
		    program->philos[i].t_think = (program->philos[i].time_to_eat - program->philos[i].time_to_sleep) + 1000;
	    else
            program->philos[i].t_think = 1000;
		pthread_mutex_init(&program->philos[i].l_fork, NULL);
        if (i == program->num_philos - 1)
			program->philos[i].r_fork = &program->philos[0].l_fork;
		else
			program->philos[i].r_fork = &program->philos[i + 1].l_fork;
        program->philos[i].write_lock = &program->write_lock;
        program->philos[i].dead_lock = program->dead_lock;
        program->philos[i].meal_lock = program->meal_lock;
        program->philos[i].program = program; 
        i++;
    }
        program->start_time = get_current_time();
}


void initialize_program(t_program *program, int num_philos, size_t time_to_die, size_t time_to_eat, size_t time_to_sleep)
{
    program->num_philos = num_philos;
    program->dead_flag = 0;

    init_global_mutexes(program);
    init_philosophers(program, num_philos, time_to_die, time_to_eat, time_to_sleep);
}


void destroy_program(t_program *program) 
{
    int i = 0;

    while (i < program->num_philos) 
    {
		pthread_mutex_destroy(&program->philos[i].l_fork);
        i++;
    }
    pthread_mutex_destroy(&program->dead_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->ready);
    pthread_mutex_destroy(&program->check_eat);
    pthread_mutex_destroy(&program->mutex_begin);
    pthread_mutex_destroy(&program->m_time);
    pthread_mutex_destroy(&program->test);

    free(program->philos);
}


