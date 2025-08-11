/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:54:21 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/11 21:42:33 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_cpy(char *read_from_fd, char **next_line)
{
	char	*temp_next;
	int		next_len;
	int		read_len;

	read_len = ft_strlen(read_from_fd);
	next_len = ft_strlen(*next_line);
	temp_next = *next_line;
	*next_line = malloc(next_len + read_len + 1);
	if (*next_line)
	{
		return (FALSE);
	}
	ft_memmove(*next_line, temp_next, next_len, 0);
	ft_memmove(*next_line, read_from_fd, read_len, next_len);
	*next_line[next_len + read_len] = '\0';
	return (TRUE);
}

int	print_error(char *read_from_fd, char **static_buffer, char *message)
{
	write(2, message, ft_strlen(message));
	if (*static_buffer)
		free(*static_buffer);
	if (read_from_fd)
		free(read_from_fd);
	return (FALSE);
}

int	cut_static_buffer(char **static_buffer, char **next_line)
{
	int		len;
	char	*temp;

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
	*next_line = NULL;
	return (TRUE);
}

int	read_fd(char **static_buffer, int fd, char **next_line)
{
	char	*read_from_fd;
	int		bytes;

	read_from_fd = malloc(BUFFER_SIZE + 1);
	if (!read_from_fd)
		return (print_error(NULL, static_buffer, "Memory allocation failed\n"));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, read_from_fd, BUFFER_SIZE);
		if (bytes == -1)
			return (print_error(read_from_fd, static_buffer, "Read process failed\n"));
		read_from_fd[bytes] = '\0';
		if (ft_strchr(read_from_fd, '\n'))
		{
			if (!str_cpy(read_from_fd, next_line))
				return (print_error(read_from_fd, static_buffer, "Memory allocation failed\n"));
			break ;
		}
		else if (!str_cpy(read_from_fd, next_line))
			return (print_error(read_from_fd, static_buffer, "Memory allocation failed\n"));
	}

	if (*static_buffer)
	{
		// Eğer buffer doluysa read_from_fd 'nin başına bu buffer'ı ekle
		// Sonrasında static buffer'ı free'le ve NULL yap
	}
	// read_from_fd'de new line sonrası eleman varsa buradan itibaren
	// Hepsini buffer'a ekle ve yeni satırı döndür.
}

int	check_new_line_from_buffer(char **static_buffer, char **next_line)
{
	*next_line = NULL;
	if (*static_buffer)
	{
		// BUFFER NULL DEĞİLSE ÖNCE BUFFER İŞLENİCEK
		// Buradan new_line'lı satır gelirse
		// static'den new_line'a olan kadar yer kesilecek
		// Kesilen yer ayrılamazsa (malloc hatası) FALSE dönülecek.
		// static buffer güncellenecek
		// sonra yeni satır dönülecek
		// eğer new_line yok ise aşağıdan devam edilecek.
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
	/* code */
	return 0;
}
