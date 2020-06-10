/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:29:58 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:30:00 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

static void		ft_set_str(char *str, size_t index, int n)
{
	if (n / 10 > 0)
		ft_set_str(str, index - 1, n / 10);
	str[index] = n % 10 + '0';
}

static char		*ft_set_str_handler(size_t str_len, int n)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	if (n > 0)
		ft_set_str(str, str_len - 1, n);
	else if (n == INT_MIN)
	{
		str[0] = '-';
		str[1] = '2';
		n += 2000000000;
		n *= -1;
		ft_set_str(str, str_len - 1, n);
	}
	else if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		ft_set_str(str, str_len - 1, n);
	}
	else if (n == 0 || n == -0)
		str[0] = '0';
	str[str_len] = '\0';
	return (str);
}

static size_t	ft_get_str_len(int n, size_t len)
{
	if (n / 10 > 0)
		len += ft_get_str_len(n / 10, len);
	len += 1;
	return (len);
}

static size_t	ft_get_str_len_handler(int n)
{
	size_t str_len;

	str_len = 0;
	if (n > 0)
		str_len = ft_get_str_len(n, str_len);
	else if (n == INT_MIN)
	{
		n += 2000000000;
		str_len = ft_get_str_len(n * -1, str_len);
		str_len += 2;
	}
	else if (n < 0)
	{
		str_len = ft_get_str_len(n * -1, str_len);
		str_len += 1;
	}
	else
		str_len = 1;
	return (str_len);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	str_len;

	str_len = ft_get_str_len_handler(n);
	str = ft_set_str_handler(str_len, n);
	return (str);
}
