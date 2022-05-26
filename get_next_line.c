/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 15:57:56 by dkocob        #+#    #+#                 */
/*   Updated: 2022/05/26 21:45:12 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

size_t	ft_strlcpy(char *d, char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i] && i < len - 1)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (i);
}

size_t	dc(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*gnl(int fd, char *line)
{
	static char	re[BUFFER_SIZE + 1];

	int i = 1;
	line[0] = '\0';
	if (dc(re, '\n') != dc(re, '\0'))
	{
		ft_strlcpy(line, re, dc(re, '\n') + 2);
		ft_strlcpy(re, &re[dc(re, '\n') + 1], dc(&re[dc(re, '\n') + 1], '\0') + 1);
		return (line);
	}
	if (re[0] != '\0')
	{
		ft_strlcpy(line, re, dc(re, '\0') + 2);
	}
	re[0] = '\0';
	while (i && dc(re, '\n') == dc(re, '\0'))
	{
		i = read(fd, re, BUFFER_SIZE);
		if (i < 0)
		{
			free (line);
			return (NULL);
		}
		re[i] = '\0';
		ft_strlcpy(&line[dc(line, '\0')], re, dc(re, '\n') + 2);
	}
	if (i == 0 && re[0] == '\0' && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	if (dc(re, '\n') != dc(re, '\0'))
		ft_strlcpy(re, &re[dc(re, '\n') + 1], dc(&re[dc(re, '\n') + 1], '\0') + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = malloc(sizeof(char) * 200000);
	if (!line)
		return (NULL);
	return (gnl(fd, line));
}