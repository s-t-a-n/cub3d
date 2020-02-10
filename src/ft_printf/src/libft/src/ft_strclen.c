/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 18:21:03 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/18 20:39:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strclen(const char *s, char c)
{
	const char	*s_orig = s;

	while (*s && *s != c)
		s++;
	return ((size_t)s - (size_t)s_orig);
}
