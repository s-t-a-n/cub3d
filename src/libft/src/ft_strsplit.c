/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:01:07 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:01:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_get_skip_len(const char *s, char c)
{
	const char *s_orig = s;

	while (s && *s && *s == c)
		s++;
	return ((size_t)s - (size_t)s_orig);
}

/*
** if you always want a string on position 0, add the following below the
** return:
** if (s && elem_cnt == 0)
**		elem_cnt++;
*/

static size_t	ft_get_elem_cnt(char *s, char c)
{
	size_t	elem_cnt;

	elem_cnt = 0;
	s += ft_get_skip_len(s, c);
	while (s && *s)
	{
		if (*s != c)
		{
			elem_cnt++;
			s += ft_strclen(s, c);
		}
		s += ft_get_skip_len(s, c);
	}
	return (elem_cnt);
}

/*
** return empty string[0] and NULL[1] when s contains only delimiters or !string
** alternative: if s == NULL return **array with NULL[0]
*/

char			**ft_strsplit(char const *s, char c)
{
	size_t	elem_cnt;
	size_t	elem_len;
	size_t	array_ctr;
	char	**array;

	elem_cnt = ft_get_elem_cnt((char *)s, c);
	array = (char **)malloc(sizeof(char *) * (elem_cnt + 1));
	if (!array)
		return (NULL);
	array_ctr = 0;
	s += ft_get_skip_len(s, c);
	while (array_ctr < elem_cnt)
	{
		elem_len = ft_strclen(s, c);
		array[array_ctr] = ft_strsub(s, 0, elem_len);
		if (array[array_ctr] == NULL)
			return (ft_arrayclear((void *)array, array_ctr + 1));
		s += elem_len;
		s += ft_get_skip_len(s, c);
		array_ctr++;
	}
	array[array_ctr] = NULL;
	return (array);
}
