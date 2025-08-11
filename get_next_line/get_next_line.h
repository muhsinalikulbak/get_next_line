/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:57:39 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/11 19:51:28 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LUNE


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6174
#endif
# define TRUE 1
# define FALSE 0

#include <unistd.h>
#include <stdlib.h>
void	*ft_memmove(void *dst, const void *src, size_t len, int start);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);







#endif
