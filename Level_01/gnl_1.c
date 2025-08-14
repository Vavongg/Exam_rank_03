#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *ft_strdup(char *src)
{
	int i = 0;
	char *dest;

	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return NULL;
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char *gnl(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 0;
	static int b_read = 0;
	char line[70000];
	int i = 0;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		if (pos >= b_read)
		{
			b_read = read(fd, buffer, BUFFER_SIZE);
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
	return (ft_strdup(line));
}

int main (int ac, char **av)
{
	int fd;
	char *str;
	(void)ac;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((str = gnl(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return 0;
}
