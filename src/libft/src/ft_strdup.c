/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:36 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:38 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strdup(const char *s1)
{
	const size_t	dst_len = ft_strlen((char *)s1) + 1;
	char			*dst;

	dst = malloc(sizeof(char) * dst_len);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, dst_len);
	return (dst);
}
