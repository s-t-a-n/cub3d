/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcount.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/09 23:48:05 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 00:08:39 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t		ft_strcount(const char *s1, char c)
{
	size_t ctr;

	ctr = 0;
	while (*s1)
	{
		if (*s1 == c)
			ctr++;
		s1++;
	}
	return (ctr);
}
