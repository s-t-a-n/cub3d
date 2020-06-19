/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ulltoa_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:01:54 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:01:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int	ft_ulltoa_strlen(unsigned long long nb, int base,
		unsigned int len)
{
	if (nb > (unsigned long long)(base - 1))
		len += ft_ulltoa_strlen(nb / base, base, len);
	len += 1;
	return (len);
}

static void			ft_fill_string_lowcase(char *str, unsigned long long nb,
						int base, unsigned int index)
{
	const char ctab[36] = "0123456789abcdefghijklmnopqrstuvwxyz";

	if (nb > (unsigned long long)(base - 1))
		ft_fill_string_lowcase(str, nb / base, base, index - 1);
	str[index] = ctab[nb % base];
}

static void			ft_fill_string_upcase(char *str, unsigned long long nb,
						int base, unsigned int index)
{
	const char ctab[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (nb > (unsigned long long)(base - 1))
		ft_fill_string_upcase(str, nb / base, base, index - 1);
	str[index] = ctab[nb % base];
}

char				*ft_ulltoa_base(unsigned long long nb, int base,
						int uppercase)
{
	unsigned int	len;
	char			*str;

	if (base < 2 || base > 36)
		return (ft_strdup(""));
	len = ft_ulltoa_strlen(nb, base, 0);
	str = ft_calloc(sizeof(char), (len + 1));
	if (str)
	{
		if (uppercase)
			ft_fill_string_upcase(str, nb, base, len - 1);
		else
			ft_fill_string_lowcase(str, nb, base, len - 1);
	}
	return (str);
}
