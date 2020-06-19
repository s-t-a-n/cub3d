/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:57:35 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:58:30 by sverschu      ########   odam.nl         */
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
