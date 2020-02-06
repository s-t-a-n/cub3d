/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ldtoa2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/21 19:31:08 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/30 00:32:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#include "libft.h"

#define DTOA_WSIZE 2024
#define DTOA_MAX_PRECISION 100

void		ft_perform_bankers_rounding(long double nb, char *worker,
						size_t worker_len)
{
	int					ctr;
	unsigned long long	nb_asint;

	ctr = 0;
	nb_asint = (unsigned long long)nb;
	while (ctr < DTOA_MAX_PRECISION)
	{
		nb = 10.0 * (nb - nb_asint);
		nb_asint = (unsigned long long)nb;
		if (nb_asint > 0)
		{
			worker[worker_len > 0 ? worker_len - 1 : 0]++;
			break ;
		}
		ctr++;
	}
}

void		ft_perform_retrospective_rounding(char *worker,
					size_t worker_len, char *master)
{
	char	*tmp;

	while (worker_len > 0 && worker[worker_len - 1] == '9')
	{
		worker[worker_len - 1] = '0';
		worker_len--;
	}
	if (worker_len == 0)
	{
		tmp = ft_ulltoa_base(ft_strtoull(&master[master[0] == '-' ? 1 : 0],
				NULL, 10) + 1, 10, __lowcase);
		ft_strlcpy(&master[master[0] == '-' ? 1 : 0], tmp, DTOA_WSIZE - 1);
		master[ft_strnlen(master, DTOA_WSIZE)] =
				(worker[0] == '\0') ? '\0' : '.';
		free(tmp);
	}
	else if (worker[0])
		worker[worker_len - 1]++;
}

void		ft_handle_integer_rounding(unsigned long long nb_asint,
					char *master)
{
	char *tmp;

	if (nb_asint > 4)
	{
		tmp = ft_ulltoa_base(ft_strtoull(&master[master[0] == '-' ? 1 : 0],
					NULL, 10) + 1, 10, __lowcase);
		ft_strlcpy(&master[master[0] == '-' ? 1 : 0], tmp, DTOA_WSIZE - 1);
		free(tmp);
	}
}

void		ft_handle_rounding(long double nb, char *worker, char *master)
{
	unsigned long long	nb_asint;
	size_t				worker_len;

	nb_asint = (unsigned long long)nb;
	nb = 10.0 * (nb - nb_asint);
	nb_asint = (unsigned long long)nb;
	worker_len = ft_strnlen(worker, DTOA_WSIZE);
	if (worker_len == 0)
	{
		ft_handle_integer_rounding(nb_asint, master);
		return ;
	}
	if (nb_asint > 5)
	{
		if (worker[worker_len > 0 ? worker_len - 1 : 0] == '9')
			ft_perform_retrospective_rounding(worker, worker_len, master);
		else
			worker[worker_len > 0 ? worker_len - 1 : 0]++;
	}
	else if (nb_asint == 5)
		ft_perform_bankers_rounding(nb, worker, worker_len);
}
