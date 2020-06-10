/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dtoa_sc1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:28:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:28:57 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#include "libft.h"
#include "ft_std.h"
#include "ft_dtoa_sc.h"

static void		ft_handle_exponent(int *exp, int *exp_ptr, char *worker)
{
	char *tmp;

	tmp = ft_itoa(*exp);
	if (tmp)
	{
		if (*exp < 10)
			ft_strlcat(worker, "0", DTOA_WSIZE);
		ft_strlcat(worker, tmp, DTOA_WSIZE);
		free(tmp);
	}
	if (exp_ptr)
		*exp_ptr = *exp;
}

static void		ft_handle_decimal(double nb, int precision, char *master)
{
	char worker[DTOA_WSIZE];

	ft_memset(worker, '\0', DTOA_WSIZE);
	ft_handle_precision_sc(&nb, precision, worker);
	ft_handle_rounding_sc(nb, worker, master);
	ft_strlcat(master, worker, DTOA_WSIZE);
	return ;
}

static void		ft_handle_integer(double *nb, int *exp, char *worker)
{
	if (*nb < 0.0 || 1.0 / *nb < 0)
	{
		ft_strlcat(worker, "-", DTOA_WSIZE);
		*nb *= -1.0;
	}
	if (*nb / 10.0 == 0 && (unsigned long long)*nb == 0)
	{
		ft_strlcat(worker, "0", DTOA_WSIZE);
		return ;
	}
	while (*nb > 10.0)
	{
		(*exp)++;
		*nb /= 10.0;
	}
	worker[ft_strnlen(worker, DTOA_WSIZE)] = (char)*nb + '0';
	return ;
}

static t_bool	ft_handle_exceptions(double nb, char *worker,
						t_bool uppercase)
{
	if (nb > LDBL_MAX)
	{
		ft_strlcat(worker, uppercase ? "INF" : "inf", DTOA_WSIZE);
		return (true);
	}
	else if (nb < -1 * LDBL_MAX)
	{
		ft_strlcat(worker, uppercase ? "-INF" : "-inf", DTOA_WSIZE);
		return (true);
	}
	else if (nb != nb)
	{
		ft_strlcat(worker, uppercase ? "NAN" : "nan", DTOA_WSIZE);
		return (true);
	}
	return (false);
}

char			*ft_dtoa_sc(double nb, int precision, int *exp_ptr,
					t_bool uppercase)
{
	char			worker[DTOA_WSIZE];
	char			*finstr;
	int				exp;

	ft_memset(worker, '\0', DTOA_WSIZE);
	if (ft_handle_exceptions(nb, worker, uppercase))
		return (ft_strdup(worker));
	exp = 0;
	ft_handle_integer(&nb, &exp, worker);
	if (precision > 0)
		ft_strlcat(worker, ".", DTOA_WSIZE);
	ft_handle_decimal(nb, precision, worker);
	if (!uppercase)
		ft_strlcat(worker, "e+", DTOA_WSIZE);
	else
		ft_strlcat(worker, "E+", DTOA_WSIZE);
	ft_handle_exponent(&exp, exp_ptr, worker);
	finstr = ft_strndup(worker, DTOA_WSIZE);
	return (finstr);
}
