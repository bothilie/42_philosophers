#include "philo_two.h"


t_arg   *parse_args(int argc, char **argv) //protéger si pas des chiffres
{
    t_arg   *args;
    int i;
    int j;
    i = 1;
    while(i < argc)
    {
        j = 0;
        while(argv[i][j])
        {
            if (!ft_isdigit(argv[i][j]))
                return NULL;
            j++;
        }
        i++;
    }
    if (!(args = (t_arg *)malloc(sizeof(t_arg)))) //MALLOC
        return(0);
    args->nb_philo = ft_atoi(argv[1]);
    args->t_to_die = ft_atoi(argv[2]);
    args->t_to_eat = ft_atoi(argv[3]);
    args->t_to_sleep = ft_atoi(argv[4]);
    args->nb_eat = 0;
    if (argc == 6)
        args->nb_eat = ft_atoi(argv[5]);
    return args;
}