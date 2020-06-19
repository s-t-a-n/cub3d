/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:00:08 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:00:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_alt;
	size_t			s_len;
	unsigned int	ctr;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	s_len = ft_strlen((char *)s);
	if (s_len > UINT_MAX)
		return (NULL);
	s_alt = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s_alt)
		return (NULL);
	ctr = 0;
	while (s[ctr] != '\0')
	{
		s_alt[ctr] = f(ctr, s[ctr]);
		ctr++;
	}
	s_alt[ctr] = '\0';
	return (s_alt);
}
