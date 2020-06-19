/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:00:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst,
				const char *src, size_t dstsize)
{
	const char *src_orig = src;

	while (dstsize > 1 && *src)
	{
		*dst = *src;
		dstsize--;
		dst++;
		src++;
	}
	if (dstsize != 0)
		*dst = '\0';
	while (*src)
		src++;
	return ((size_t)src - (size_t)src_orig);
}
