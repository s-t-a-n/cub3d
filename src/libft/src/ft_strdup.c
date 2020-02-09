/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 20:59:34 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/15 18:59:59 by sverschu      ########   odam.nl         */
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
