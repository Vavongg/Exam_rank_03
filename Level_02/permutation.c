#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i;
	
	i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void sorted(char *str)
{
	char 	tmp;
	int		i = 0;
	int		j;

	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	permut(char *str, char *res, int *used, int len, int pos)
{
    int i = 0;

	if (pos == len)
	{
        puts(res);
        return;
    }
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			res[pos] = str[i];
			permut(str, res, used, len, pos + 1);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int len = ft_strlen(av[1]);
	char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));

	if(!result || !used)
		return 1;
	if (ac != 2)
		return 1;
	sorted(av[1]);
    permut(av[1], result, used, len, 0);
    free(result);
    free(used);
	return 0;
}
