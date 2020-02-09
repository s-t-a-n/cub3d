/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:57:06 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/18 20:27:44 by sverschu      ########   odam.nl         */
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
