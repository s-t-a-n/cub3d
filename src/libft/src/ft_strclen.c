/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:27 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:28 by sverschu      ########   odam.nl         */
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
