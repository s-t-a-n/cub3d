/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoa1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:30:04 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:30:06 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#include "ft_ldtoa.h"
#include "libft.h"

static void		ft_handle_precision(long double *nb, int precision,
					char *worker)
{
	int					ctr;
	unsigned long long	nb_asint;

	ctr = 0;
	nb_asint = (unsigned long long)*nb;
	while (ctr < precision)
	{
		*nb = 10.0 * (*nb - nb_asint);
		nb_asint = (unsigned long long)*nb;
		worker[ctr] = (char)nb_asint + '0';
		ctr++;
	}
}

static char		*ft_handle_decimal(long double nb, int precision, char *master)
{
	char worker[DTOA_WSIZE];

	ft_memset(worker, '\0', DTOA_WSIZE);
	ft_handle_precision(&nb, precision, worker);
	ft_handle_rounding(nb, worker, master);
	return (ft_strndup(worker, DTOA_WSIZE));
}

static char		*ft_handle_integer(long double *nb)
{
	char				worker[DTOA_WSIZE];
	char				*tmp;

	ft_memset(worker, '\0', DTOA_WSIZE);
	if (*nb < 0.0 || 1.0 / *nb < 0)
	{
		ft_strlcat(worker, "-", DTOA_WSIZE);
		*nb *= -1.0;
	}
	if (*nb / 1.0 == 0.0)
	{
		ft_strlcat(worker, "0", DTOA_WSIZE);
		return (ft_strndup(worker, DTOA_WSIZE));
	}
	tmp = ft_ulltoa_base((unsigned long long)*nb, 10, __lowcase);
	if (tmp)
	{
		ft_strlcat(worker, tmp, DTOA_WSIZE);
		free(tmp);
	}
	return (ft_strndup(worker, DTOA_WSIZE));
}

static int		ft_handle_exceptions(long double nb, char *worker)
{
	if (nb > LDBL_MAX)
	{
		ft_strlcat(worker, "inf", DTOA_WSIZE);
		return (1);
	}
	else if (nb < -1 * LDBL_MAX)
	{
		ft_strlcat(worker, "-inf", DTOA_WSIZE);
		return (1);
	}
	else if (nb != nb)
	{
		ft_strlcat(worker, "nan", DTOA_WSIZE);
		return (1);
	}
	return (0);
}

char			*ft_ldtoa(long double nb, int precision)
{
	char			worker[DTOA_WSIZE];
	char			*tmp;
	char			*finstr;

	ft_memset(worker, '\0', DTOA_WSIZE);
	if (ft_handle_exceptions(nb, worker))
		return (ft_strdup(worker));
	tmp = ft_handle_integer(&nb);
	if (tmp)
	{
		ft_strlcat(worker, tmp, DTOA_WSIZE);
		free(tmp);
	}
	if (precision > 0)
		ft_strlcat(worker, ".", DTOA_WSIZE);
	tmp = ft_handle_decimal(nb, precision, worker);
	if (tmp)
	{
		ft_strlcat(worker, tmp, DTOA_WSIZE);
		free(tmp);
	}
	finstr = ft_strndup(worker, DTOA_WSIZE);
	return (finstr);
}
