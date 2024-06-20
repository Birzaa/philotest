#include "philo.h"

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [num_meals]\n", argv[0]);
        return 1;
    }
    t_program program;
    parsing(argv);
    program.start = 0;
    int num_philos = atoi(argv[1]);
    size_t time_to_die = atoi(argv[2]) * 1000;
    size_t time_to_eat = atoi(argv[3]) * 1000;
    size_t time_to_sleep = atoi(argv[4]) * 1000;
    program.nb_must_eat = -1;
    if (argc == 6)
    {
        program.nb_must_eat = atoi(argv[5]);
    }
    initialize_program(&program, num_philos, time_to_die, time_to_eat, time_to_sleep);
    create_philo_threads(&program, num_philos);
    monitor_philos(&program);
    join_philo_threads(&program, num_philos);
    destroy_program(&program);
    return 0;
}
