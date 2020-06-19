/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:00:31 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:00:33 by sverschu      ########   odam.nl         */
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
