/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:32:49 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/15 18:54:38 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	const void *b_orig = b;

	while (len > 0)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
		len--;
	}
	return ((void *)b_orig);
}
