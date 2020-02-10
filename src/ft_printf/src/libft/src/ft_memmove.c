/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:03:23 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/18 20:47:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_rev(void *dst, const void *src, size_t len)
{
	const void		*orig_dst = dst;

	dst += len - 1;
	src += len - 1;
	while (len > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst--;
		src--;
		len--;
	}
	return ((void *)orig_dst);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (len == 0 || dst == src)
		return (dst);
	else if (src > dst)
		return (ft_memcpy(dst, src, len));
	else
		return (ft_memcpy_rev(dst, src, len));
}
