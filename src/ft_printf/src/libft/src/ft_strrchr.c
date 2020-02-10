/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:46:23 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/16 19:35:52 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char	*s_hit;

	s_hit = NULL;
	while (*s)
	{
		if (*s == (char)c)
			s_hit = (char *)s;
		s++;
	}
	if (*s == (char)c)
		s_hit = (char *)s;
	return (s_hit);
}
