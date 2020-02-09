/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 16:47:34 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/23 21:37:37 by sverschu      ########   odam.nl         */
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
