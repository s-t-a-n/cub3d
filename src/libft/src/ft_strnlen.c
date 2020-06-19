/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:00:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:00:25 by sverschu      ########   odam.nl         */
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
