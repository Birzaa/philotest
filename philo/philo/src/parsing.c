#include "philo.h"

long int	ft_long_atoi(const char *nptr)
{
	int			i;
	int			n;
	long int	nb;

	i = 0;
	n = 1;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -n;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * n);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_number(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_number(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_long_atoi(av[i]) > 2147483647 || ft_strlen(av[i]) > 11)
			return (1);
		i++;
	}
	return (0);
}

void parsing(char **av)
{
	if (is_number(av) || ft_check_number(av))
		exit(1);
	else if (!ft_long_atoi(av[1]))
		exit(1);
}