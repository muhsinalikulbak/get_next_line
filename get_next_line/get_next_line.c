/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:19:53 by mkulbak           #+#    #+#             */
/*   Updated: 2025/08/12 15:48:51 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_read_len(char *read_from_fd, int is_new_line)
{
	char	*new_line_position;

	if (is_new_line)
	{
		new_line_position = ft_strchr(read_from_fd, '\n');
		return (new_line_position - read_from_fd + 1);
	}
	return (ft_strlen(read_from_fd));
}

int	str_cpy(char *read_from_fd, char **next_line, int is_new_line)
{
	char	*temp_next;
	int		next_len;
	int		read_len;

	read_len = get_read_len(read_from_fd, is_new_line);
	next_len = 0;
	if (*next_line)
		next_len = ft_strlen(*next_line);
	temp_next = *next_line;
	*next_line = malloc(next_len + read_len + 1);
	if (!*next_line)
	{
		if (temp_next)
			free(temp_next);
		return (FALSE);
	}
	if (temp_next)
		ft_memmove(*next_line, temp_next, next_len, 0);
	ft_memmove(*next_line, read_from_fd, read_len, next_len);
	(*next_line)[next_len + read_len] = '\0';
	if (temp_next)
		free(temp_next);
	return (TRUE);
}

int	join_static_buffer(char **static_buffer, char **next_line)
{
	int		len;
	char	*temp;

	if (!*static_buffer)
		return (TRUE);
	if (!*next_line)
	{
		*next_line = ft_strdup(*static_buffer);
		if (!*next_line)
			return (FALSE);
		free(*static_buffer);
		*static_buffer = NULL;
		return (TRUE);
	}
	len = ft_strlen(*static_buffer) + ft_strlen(*next_line);
	temp = malloc(len + 1);
	if (!temp)
		return (FALSE);
	ft_memmove(temp, *static_buffer, ft_strlen(*static_buffer), 0);
	ft_memmove(temp, *next_line, ft_strlen(*next_line), ft_strlen(*static_buffer));
	temp[len] = '\0';
	free(*next_line);
	free(*static_buffer);
	*static_buffer = NULL;
	*next_line = temp;
	return (TRUE);
}

int	last_process(char **static_buffer, char *read_from_fd, char **next_line)
{
	char	*after_new_line;
	char	*newline_pos;
	
	if (!join_static_buffer(static_buffer, next_line))
	{
		if (*static_buffer)
			free(*static_buffer);
		if (read_from_fd)
			free(read_from_fd);
		return (FALSE);
	}
	newline_pos = ft_strchr(read_from_fd, '\n');
	if (newline_pos)
	{
		after_new_line = newline_pos + 1;
		*static_buffer = ft_strdup(after_new_line);
		if (!*static_buffer)
		{
			if (read_from_fd)
				free(read_from_fd);
			return (FALSE);
		}
	}
	free(read_from_fd);
	return (TRUE);
}

int	cleanup_and_return(char **static_buffer, char *read_from_fd, int ret_val)
{
	if (*static_buffer)
		free(*static_buffer);
	if (read_from_fd)
		free(read_from_fd);
	return (ret_val);
}

int	handle_newline(char **static_buffer, char *read_from_fd, char **next_line)
{
	if (!str_cpy(read_from_fd, next_line, TRUE))
		return (cleanup_and_return(static_buffer, read_from_fd, FALSE));
	if (!last_process(static_buffer, read_from_fd, next_line))
		return (FALSE);
	return (TRUE);
}

int	read_fd(char **static_buffer, int fd, char **next_line)
{
	char	*read_from_fd;
	int		bytes;

	bytes = 1;
	while (bytes > 0)
	{
		read_from_fd = malloc(BUFFER_SIZE + 1);
		if (!read_from_fd)
			return (cleanup_and_return(static_buffer, NULL, FALSE));
		bytes = read(fd, read_from_fd, BUFFER_SIZE);
		if (bytes == -1)
			return (cleanup_and_return(static_buffer, read_from_fd, FALSE));
		read_from_fd[bytes] = '\0';
		if (bytes == 0)
		{
			free(read_from_fd);
			break ;
		}
		if (ft_strchr(read_from_fd, '\n'))
			return (handle_newline(static_buffer, read_from_fd, next_line));
		if (!str_cpy(read_from_fd, next_line, FALSE))
			return (cleanup_and_return(static_buffer, read_from_fd, FALSE));
		free(read_from_fd);
	}
	if (!join_static_buffer(static_buffer, next_line))
		return (FALSE);
	return (TRUE);
}

int	check_new_line_from_buffer(char **static_buffer, char **next_line)
{
	char	*after_new_line;
	char	*temp;
	int		len;

	*next_line = NULL;
	if (*static_buffer && ft_strchr(*static_buffer, '\n'))
	{
		after_new_line = ft_strchr(*static_buffer, '\n') + 1;
		len = ft_strlen(*static_buffer) - ft_strlen(after_new_line);
		*next_line = malloc(len + 1);
		if (!*next_line)
		{
			free (*static_buffer);
			*static_buffer = NULL;
			return (FALSE);
		}
		ft_memmove(*next_line, *static_buffer, len, 0);
		(*next_line)[len] = '\0';
		temp = *static_buffer;
		*static_buffer = ft_strdup(after_new_line);
		if (!*static_buffer)
		{
			free(*next_line);
			free(temp);
			return (FALSE);
		}
		free(temp);
	}
	return (TRUE);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 )
		return (NULL);
	next_line = NULL;
	check = check_new_line_from_buffer(&buffer, &next_line);
	if (!check)
		return (NULL);
	else if (next_line)
		return (next_line);
	check = read_fd(&buffer, fd, &next_line);
	if (!check)
	{
		if (next_line)
			free(next_line);
		return (NULL);
	}
	else if (next_line)
		return (next_line);
	return (NULL);
}

int main(void)
{
	int fd = open("file", O_RDONLY);
	char	*line;

	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
