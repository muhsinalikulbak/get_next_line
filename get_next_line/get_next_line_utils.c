/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:50:05 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/12 15:10:51 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char	*s1)
{
	int		i;
	int		len;
	char	*heap_str;

	i = 0;
	len = ft_strlen(s1) + 1;
	heap_str = (char *)malloc(sizeof(char) * len);
	if (!heap_str)
		return (NULL);
	while (s1[i])
	{
		*(heap_str + i) = s1[i];
		i++;
	}
	heap_str[i] = '\0';
	return (heap_str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t len, int start)
{
	size_t	i;

	if (!src && !dst)
		return (NULL);
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			*((unsigned char *)dst + start + len) = *((unsigned char *)src + len);
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*((unsigned char *)dst + start + i) = *((unsigned char *)src + i);
			i++;
		}
				
	}	
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
