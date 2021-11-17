/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 15:57:56 by dkocob        #+#    #+#                 */
/*   Updated: 2021/11/17 22:02:15 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
# define BUFFER_SIZE 3

size_t	ft_strlcpy(char *d, char *s, int len)
{
	size_t	i;

	i = 0;
	while (s[i] && i < len)
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

char	*gnl(int fd, char *line, int i, int pos)
{
	static char	re[BUFFER_SIZE + 1];

	if (dc(re, '\n') != dc(re, '\0'))
	{
		ft_strlcpy(line, re, dc(re, '\n'));
		ft_strlcpy(re, &re[dc(re, '\n') + 1], dc(&re[dc(re, '\n')], '\0'));
		return (line);
	}
	if (re[0] != '\0')
	{
		pos += dc(re, '\0');
		ft_strlcpy(line, re, pos);
		re[0] = '\0';
	}
	while (i && dc(re, '\n') == dc(re, '\0'))
	{
		i = read(fd, re, BUFFER_SIZE);
		ft_strlcpy(&line[pos], re, dc(re, '\n'));
		pos += i;
	}
	if (i == 0 && re[0] == '\0' && line[0] == '\0')
		return (NULL);
	ft_strlcpy(re, &re[dc(re, '\n') + 1], dc(&re[dc(re, '\n')], '\0'));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;

	line = malloc(sizeof(char) * 20000000);
	if (!line)
		return (NULL);
	return (gnl(fd, line, 1, 0));
}
