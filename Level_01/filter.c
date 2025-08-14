#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!new)
        return NULL;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return new;
}

char *get_stdin(void)
{
    static char buffer[1024];
    static int pos = 0;
    static int b_read = 0;
    char line[70000];
    int i = 0;

    while (1)
    {
        if (pos >= b_read)
        {
            b_read = read(0, buffer, 1024);
            pos = 0;
            if (b_read <= 0)
                break;
        }
        line[i++] = buffer[pos++];
        if (line[i - 1] == '\n')
            break;
    }
    if (i == 0)
        return NULL;
    line[i] = '\0';
    return ft_strdup(line);
}

char *str_filter(char *str, char *filter)
{
    char *new = ft_strdup(str);
    int i = 0;
    int len = ft_strlen(filter);

    while (str[i])
    {
        if (str[i] == filter[0])
        {
            int j = 1;
            while (j < len && str[i + j] == filter[j])
                j++;
            if (j == len)
            {
                for (int k = 0; k < len; k++)
                    new[i + k] = '*';
                i += len - 1;
            }
        }
        i++;
    }
    return new;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    char *str = get_stdin();
    if (!str)
        return 1;
    char *filter = av[1];
    char *fstr = str_filter(str, filter);
    if (!fstr)
        return 1;
    printf("%s", fstr);
    free(str);
    free(fstr);
    return 0;
}

