/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 20:49:02 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/13 22:51:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const void		*orig_dst = dst;

	if (dst == src)
		return ((void *)orig_dst);
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		n--;
		dst++;
		src++;
	}
	return ((void *)orig_dst);
}
