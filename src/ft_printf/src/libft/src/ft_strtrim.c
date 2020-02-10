/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 18:33:15 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/07 15:08:09 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int		ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

/*
** rip this stupid protection out after the evaluation;
** there is absolutely no reason for start not to be size_t
*/

static char		*ft_strsub_wrapper(char const *s, size_t start, size_t len)
{
	if (start > UINT_MAX)
		return (NULL);
	else
		return (ft_strsub(s, (unsigned int)start, len));
}

char			*ft_strtrim(char const *s1, char const *set)
{
	const char	*s1_orig = s1;
	size_t		start;
	size_t		len;
	size_t		ctr;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	start = 0;
	while (*s1 && ft_isinset(*s1, set))
	{
		s1++;
		start++;
	}
	len = 0;
	ctr = 0;
	while (*s1)
	{
		ctr++;
		if (!ft_isinset(*s1, set))
			len = ctr;
		s1++;
	}
	return (ft_strsub_wrapper(s1_orig, start, len));
}
