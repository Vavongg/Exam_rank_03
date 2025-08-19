#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_set(int *power_set, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fprintf(stdout, "%d", power_set[i]);
		if (i < size - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
	return ;
}

void	ft_powerset(int *set, int size, int target, int index, int *power_set, int size_powerset)
{
	int	sum;
	int	i;

	if (index == size)
	{
		i = 0;
		sum = 0;
		while (i < size_powerset)
		{
			sum = sum + power_set[i];
			i++;
		}
		if (sum == target)
			print_set(power_set, size_powerset);
		return ;
	}
	power_set[size_powerset] = set[index];
	ft_powerset(set, size, target, index + 1, power_set, size_powerset + 1);
	ft_powerset(set, size, target, index + 1, power_set, size_powerset);
	return ;
}

int	main(int ac, char **av)
{
	int	*set;
	int	*power_set;
	int	size;
	int	target;
	int	i;

	if (ac < 3)
		return (1);
	target = atoi(av[1]);
	size = ac - 2;
	set = malloc(size * sizeof(int));
	if (!set)
		return (1);
	power_set = malloc(size * sizeof(int));
	if (!power_set)
		return (1);
	i = -1;
	while (++i < size)
		set[i] = atoi(av[i + 2]); 
	ft_powerset(set, size, target, 0, power_set, 0);
	free(set);
	free(power_set);
	return (0);
}