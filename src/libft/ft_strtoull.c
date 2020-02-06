/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtoull.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 00:29:35 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:50:09 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static void					ft_prehandler(const char **str, char **endptr,
								int *base)
{
	while (ft_isspace(**str))
		(*str)++;
	if (endptr)
		*endptr = (char *)*str;
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

static int					ft_numeric_value_for_base(char c, int base)
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

static unsigned long long	ft_strtol_handle_overflow(unsigned long long value,
								char **endptr, int base)
{
	if (endptr)
	{
		while (ft_numeric_value_for_base(**endptr, base) >= 0)
			(*endptr)++;
	}
	if (value >= ULLONG_MAX)
		return (ULLONG_MAX);
	else
		return (value);
}

unsigned long long			ft_strtoull(const char *str, char **endptr,
								int base)
{
	unsigned long long	retval;
	unsigned long long	cutoff;
	int					nbr;

	if (base < 0 || base == 1 || base > 36)
		return (0);
	ft_prehandler(&str, endptr, &base);
	cutoff = ULLONG_MAX / base;
	retval = 0;
	nbr = ft_numeric_value_for_base(*str, base);
	while (nbr >= 0)
	{
		retval = (nbr >= 0 ? retval * base + nbr : retval);
		if (retval > cutoff
			&& ft_numeric_value_for_base(*(str + 1), base) >= 0)
			return (ft_strtol_handle_overflow(ULLONG_MAX,
						endptr, base));
			str++;
		nbr = ft_numeric_value_for_base(*str, base);
	}
	return (ft_strtol_handle_overflow(retval, endptr, base));
}
