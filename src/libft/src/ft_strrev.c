/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:00:58 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:01:04 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t str_len;
	size_t ctr;

	ctr = 0;
	if (!*str)
		return (str);
	str_len = ft_strlen(str);
	while (ctr < str_len / 2)
	{
		ft_swap(&str[ctr], &str[str_len - 1 - ctr]);
		ctr++;
	}
	return (str);
}
