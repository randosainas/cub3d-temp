/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:29 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/01 14:43:37 by lpetit           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

char	*ft_fix_line(char *line)
{
	char	*tmp;

	tmp = line;
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

char	*ft_saved(char *line)
{
	size_t	i;
	char	*saved;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	saved = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!saved)
		return (NULL);
	if (*saved == '\0')
	{
		free(saved);
		saved = NULL;
	}
	line[i + 1] = '\0';
	return (saved);
}

char	*ft_read_line(int fd, char *static_buf, char *buf)
{
	char	*tmp;
	ssize_t	n;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (NULL);
		else if (n == 0)
			break ;
		buf[n] = '\0';
		if (!static_buf)
			static_buf = ft_strdup("");
		tmp = static_buf;
		static_buf = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (!static_buf)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (static_buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*static_buf;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE == 0 || BUFFER_SIZE >= 2147483647)
	{
		free(static_buf);
		static_buf = NULL;
		return (NULL);
	}
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(static_buf);
		static_buf = NULL;
		return (NULL);
	}
	line = ft_read_line(fd, static_buf, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	static_buf = ft_saved(line);
	line = ft_fix_line(line);
	return (line);
}