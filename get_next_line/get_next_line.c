/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:54:21 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/11 13:37:30 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// memmove kullan

int	read_fd(char **static_buffer, int fd, char **next_line)
{
	char	*read_from_fd;
	int		bytes;

	read_from_fd = malloc(BUFFER_SIZE + 1);
	if (!read_from_fd)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, read_from_fd, BUFFER_SIZE);
		if (bytes == -1)
		{
			// HATA VER ÇIK
		}
		if (bytes == 0)
		{
			// NE olacak bak
		}
		read_from_fd[bytes] = '\0';
		// new line arayışı yap, new_line varsa break ile kır.
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
		write(2, "Memory allocation failed\n", 13);
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
