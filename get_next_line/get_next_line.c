/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:54:21 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/12 11:58:33 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_cpy(char *read_from_fd, char **next_line, int is_new_line)
{
	char	*temp_next;
	char	*new_line_position;
	int		next_len;
	int		read_len;

	if (is_new_line)
	{
		new_line_position = ft_strchr(read_from_fd, '\n');
		read_len = new_line_position - read_from_fd + 1;
	}
	else
		read_len = ft_strlen(read_from_fd);
	next_len = ft_strlen(*next_line);
	temp_next = *next_line;
	*next_line = malloc(next_len + read_len + 1);
	if (!*next_line)
	{
		return (FALSE);
	}
	ft_memmove(*next_line, temp_next, next_len, 0);
	ft_memmove(*next_line, read_from_fd, read_len, next_len);
	*next_line[next_len + read_len] = '\0';
	return (TRUE);
}

int	print_error(char *read_from_fd, char **static_buffer, int message_type)
{
	char	*message;

	if (message_type == EMALLOC)
		message = "Memory allocation failed\n";
	else 
		message = "Read process failed\n";
	write(2, message, ft_strlen(message));
	if (*static_buffer)
		free(*static_buffer);
	if (read_from_fd)
		free(read_from_fd);
	return (FALSE);
}

int	join_static_buffer(char **static_buffer, char **next_line)
{
	int		len;
	char	*temp;

	if (!*static_buffer)
		return (TRUE);
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
	
	if (!join_static_buffer(static_buffer, next_line))
		return (print_error(read_from_fd, static_buffer, EMALLOC));
	after_new_line = ft_strchr(read_from_fd, '\n') + 1;
	*static_buffer = ft_strdup(after_new_line);
	if (!*static_buffer)
		return (print_error(read_from_fd, static_buffer, EMALLOC));
	free(read_from_fd);
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
			return (print_error(NULL, static_buffer, EMALLOC));
		bytes = read(fd, read_from_fd, BUFFER_SIZE);
		if (bytes == -1)
			return (print_error(read_from_fd, static_buffer, EREAD));
		read_from_fd[bytes] = '\0';
		if (ft_strchr(read_from_fd, '\n'))
		{
			if (!str_cpy(read_from_fd, next_line, TRUE))
				return (print_error(read_from_fd, static_buffer, EMALLOC));
			break ;
		}
		else if (!str_cpy(read_from_fd, next_line, FALSE))
			return (print_error(read_from_fd, static_buffer, EMALLOC));
		free(read_from_fd);
		read_from_fd = NULL;
	}
	if (!last_process(static_buffer, read_from_fd, next_line))
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
			return (free (*static_buffer), FALSE);
		ft_memmove(*next_line, *static_buffer, len, 0);
		*next_line[len] = '\0';
		temp = *static_buffer;
		*static_buffer = ft_strdup(after_new_line);
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


int main(int argc, char const *argv[])
{
	int fd = open("file", O_RDONLY);
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
