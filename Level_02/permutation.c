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
	int		i;
	int		j;

	i = 0;
	j = i + 1;

	while (str[i] != '\0')
	{
		while (str[j] != '\0')
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

void generate(char *str, char *result, int *used, int len, int depth)
{
    int i;

	i = 0;
	if (depth == len)
	{
        write(1, result, len);
        write(1, "\n", 1);
        return;
    }
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			result[depth] = str[i];
			generate(str, result, used, len, depth + 1);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if(ac != 2 || check_dup(av[1]))
		return 1;
	int len = ft_strlen(av[1]);
	char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));
	if(!result || !used)
		return 1;
	sorted(av[1]);
    generate(av[1], result, used, len, 0);
    free(result);
    free(used);
	return 0;
}
