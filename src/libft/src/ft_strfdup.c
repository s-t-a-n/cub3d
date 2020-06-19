/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strfdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:46 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strfdup(const char *s1, char c)
{
	const size_t	dst_len = ft_strlen((char *)s1) + 1;
	char			*dst;
	size_t			ctr;

	dst = malloc(sizeof(char) * (dst_len - ft_strcount(s1, c) + 1));
	if (!dst)
		return (NULL);
	ctr = 0;
	while (*s1)
	{
		if (*s1 != c)
		{
			dst[ctr] = *s1;
			ctr++;
		}
		s1++;
	}
	dst[ctr] = '\0';
	return (dst);
}
