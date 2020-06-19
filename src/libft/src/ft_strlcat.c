/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst,
				const char *src, size_t dstsize)
{
	size_t	dst_len;

	if (!dst && src && dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strnlen(dst, dstsize);
	if (dstsize <= dst_len)
		return (ft_strlen((char *)src) + dstsize);
	while (dstsize && *dst)
	{
		dstsize--;
		dst++;
	}
	ft_strlcpy(dst, src, dstsize);
	return (ft_strlen((char *)src) + dst_len);
}
