/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:52:25 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/18 20:27:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	const char	*s_orig = s;

	while (*s)
		s++;
	return ((size_t)s - (size_t)s_orig);
}
