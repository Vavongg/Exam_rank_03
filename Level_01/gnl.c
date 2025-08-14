#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

//1ere version de GNL

static char *ft_strjoin_free(char *s1, char *s2, int len2)
{
    int len1 = 0;
    while (s1 && s1[len1])
        len1++;
    char *res = malloc(len1 + len2 + 1);
    if (!res)
        return NULL;
    for (int i = 0; i < len1; i++)
        res[i] = s1[i];
    for (int j = 0; j < len2; j++)
        res[len1 + j] = s2[j];
    res[len1 + len2] = '\0';
    free(s1);
    return res;
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int b_read = 0;
    static int pos = 0;
    char *line = NULL;
    int i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        if (pos >= b_read)
        {
            b_read = read(fd, buffer, BUFFER_SIZE);
            pos = 0;
            if (b_read <= 0)
                return line;
        }
        i = pos;
        while (i < b_read && buffer[i] != '\n')
            i++;
        line = ft_strjoin_free(line, buffer + pos, i - pos);
        pos = i;
        if (pos < b_read && buffer[pos] == '\n')
        {
            line = ft_strjoin_free(line, "\n", 1);
            pos++;
            return line;
        }
    }
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 1;
    int fd = open(av[1], O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
