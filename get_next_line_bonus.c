/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkannane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:58:38 by tkannane          #+#    #+#             */
/*   Updated: 2023/11/23 10:36:14 by tkannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *str_line, int fd)
{
	char	*buffer;
	int		read_byte;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr(str_line, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		str_line = ft_strjoin(str_line, buffer);
	}
	free(buffer);
	return (str_line);
}

char	*get_next_line(int fd)
{
	static char	*str_line[OPEN_MAX];
	char		*r_line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (0);
	tmp = ft_read(str_line[fd], fd);
	if (!tmp)
	{
		if (str_line[fd])
			free(str_line[fd]);
		str_line[fd] = NULL;
		return (NULL);
	}
	str_line[fd] = tmp;
	r_line = ft_get_line(str_line[fd]);
	str_line[fd] = ft_get_new_str(str_line[fd]);
	return (r_line);
}
