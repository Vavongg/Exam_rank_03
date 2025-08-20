#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	int i = 0;
	char *dest = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void print_it(int n)
{
	int i = 0;
	while (i < n)
	{
		write(1, "*", 1);
		i++;
	}
}

char *ft_get_line()
{
	static char buffer[10];
	char line[100000];
	static int pos = 0;
	static int b_read = 0;
	int i = 0;
	while (1)
	{
		if (pos >= b_read)
		{
			b_read = read(0, buffer, 10);
			pos = 0;
			if (b_read == 0)
				break;
			if (b_read < 0)
			{
				perror("Error");
				return (NULL);
			}
		}
		line[i++] = buffer[pos++];
	}
	if (i == 0)
		return (NULL);
	line[i] = 0;
	return (ft_strdup(line));
}

void filter_sh(char *str, char *filter)
{
    int i = 0;
    int j;
    int len = ft_strlen(filter);

    while (str[i])
    {
        j = 0;
        while (str[i + j] && str[i + j] == filter[j])
            j++;
        if (j == len)
        {
            print_it(len);
            i += len;
        }
        else
        {
            write(1, &str[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
	char *s;

	if (argc != 2 || !argv[1][0])
		return (1);
	s = ft_get_line();
	while (s)
	{
		filter_sh(s, argv[1]);
		free(s);
		s = ft_get_line();
	}
	free(s);
	return (0);
}
