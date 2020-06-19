/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putwstr_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <wchar.h>

/*
** not optimized: calls write for every wchar_t
*/

void	ft_putwstr_fd(wchar_t *ws, int fd)
{
	if (!ws)
		return ;
	while (*ws)
	{
		ft_putwchar_fd(*ws, fd);
		ws++;
	}
}
