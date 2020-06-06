/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 00:17:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:49:48 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static void	ft_prehandler(const char **str, int *sign,
		char **endptr, int *base)
{
	while (ft_isspace(**str))
		(*str)++;
	if (endptr)
		*endptr = (char *)*str;
	*sign = (**str == '-') ? -1 : 1;
	*str += (**str == '-' || **str == '+') ? 1 : 0;
	if (**str && (*base == 0 || *base == 16)
		&& **str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
	{
		*base = 16;
		*str += 2;
	}
	else if (**str && (*base == 0 || *base == 2) && **str == '0'
			&& (*(*str + 1) == 'b' || *(*str + 1) == 'B'))
	{
		*base = 2;
		*str += 2;
	}
	else if (**str && *base == 0 && **str == '0')
		*base = 8;
	else if (*base == 0)
		*base = 10;
}

static int	ft_numeric_value_for_base(char c, int base)
{
	if (ft_isdigit(c) && c - '0' < base)
		return (c - '0');
	else if (ft_islower(c) && c - 'a' + 10 < base)
		return (c - 'a' + 10);
	else if (ft_isupper(c) && c - 'A' + 10 < base)
		return (c - 'A' + 10);
	else
		return (-1);
}

static long	ft_strtol_handle_sign_and_overflow(unsigned long value,
			int sign, char **endptr, int base)
{
	if (endptr)
	{
		if (**endptr && ft_numeric_value_for_base(*(*endptr + 1), base)
			>= 0 && (**endptr == '-' || **endptr == '+'))
			(*endptr)++;
		while (ft_numeric_value_for_base(**endptr, base) >= 0)
			(*endptr)++;
	}
	if (value >= LONG_MAX && sign == 1)
		return (LONG_MAX);
	else if (value > (unsigned long)LONG_MAX + 1 && sign == -1)
		return (LONG_MIN);
	else
		return ((long)(value * sign));
}

long		ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	retval;
	unsigned long	cutoff;
	int				nbr;
	int				sign;

	sign = 1;
	if (base < 0 || base == 1 || base > 36)
		return (0);
	ft_prehandler(&str, &sign, endptr, &base);
	cutoff = (unsigned long)(LONG_MAX + (sign == -1 ? 1 : 0)) / base;
	retval = 0;
	nbr = ft_numeric_value_for_base(*str, base);
	while (nbr >= 0)
	{
		retval = (nbr >= 0 ? retval * base + nbr : retval);
		if (retval > cutoff 
				&& ft_numeric_value_for_base(*(str + 1), base) >= 0)
		{
			return (ft_strtol_handle_sign_and_overflow(ULONG_MAX, sign, endptr,
					base));
		}
		str++;
		nbr = ft_numeric_value_for_base(*str, base);
	}
	return (ft_strtol_handle_sign_and_overflow(retval, sign, endptr, base));
}
