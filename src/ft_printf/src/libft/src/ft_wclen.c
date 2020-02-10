/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wclen.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 22:14:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 22:23:41 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "libft.h"

/*
** check how big a wchar_t in bytes is
*/

int		ft_wclen(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x7FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	else
		return (0);
}
