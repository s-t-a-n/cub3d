/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:52:03 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/13 19:38:04 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strndup(const char *s1, size_t len)
{
	char	*dst;

	if (len == 0)
		return (ft_strdup(""));
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len + 1);
	return (dst);
}
