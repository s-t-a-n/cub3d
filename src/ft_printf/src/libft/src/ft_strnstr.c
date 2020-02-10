/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 18:33:31 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/23 03:43:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack,
			const char *needle, size_t len)
{
	size_t	needle_len;

	if (needle[0] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && len >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
