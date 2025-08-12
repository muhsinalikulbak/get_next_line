/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:57:39 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/12 01:36:30 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LUNE


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
# define TRUE 1
# define FALSE 0
# define EMALLOC 2
# define EREAD 3

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
void	*ft_memmove(void *dst, const void *src, size_t len, int start);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char	*s1);





#endif
