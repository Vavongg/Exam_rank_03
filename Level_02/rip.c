#include <stdio.h>
#include <unistd.h>

int    ft_strlen(char *s)
{
    int    i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int    balanced(char *s)
{
    int    i;
    int    open;
    int    closes;

    i = 0;
    open = 0;
    closes = 0;
    while (s[i])
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;
            else
                closes++;
        }
        i++;
    }
    return (open + closes);
}

void    bt(int i, int to_remove, int removed, char *s)
{
    char    tmp;

    if (i == ft_strlen(s))
    {
        if (!balanced(s) && to_remove == removed)
            puts(s);
        return ;
    }
    if (removed > to_remove)
        return ;
    if (s[i] == '(' || s[i] == ')')
    {
        tmp = s[i];
        s[i] = ' ';
        bt(i + 1, to_remove, removed + 1, s);
        s[i] = tmp;
        bt(i + 1, to_remove, removed, s);
    }
    else
        bt(i + 1, to_remove, removed, s);
}

int    main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == '\0')
    {
        write(1, "\n", 1);
        return (1);
    }
    if (!balanced(av[1]))
    {
        puts(av[1]);
        return (0);
    }
    bt(0, balanced(av[1]), 0, av[1]);
}
