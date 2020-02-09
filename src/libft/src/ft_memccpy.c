/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 19:03:28 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/15 20:11:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** only copy if dst != src
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	if (dst == src)
		return (ft_memchr(dst, c, n) + 1);
	else
		while (n > 0)
		{
			*(unsigned char *)dst = *(unsigned char *)src;
			dst++;
			if (*(unsigned char *)src == (unsigned char)c)
				return (dst);
			src++;
			n--;
		}
	return (NULL);
}
