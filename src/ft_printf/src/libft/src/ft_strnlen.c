/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 21:49:04 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/23 21:26:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*s_orig = s;

	while (*s && maxlen > 0)
	{
		s++;
		maxlen--;
	}
	return ((size_t)s - (size_t)s_orig);
}
