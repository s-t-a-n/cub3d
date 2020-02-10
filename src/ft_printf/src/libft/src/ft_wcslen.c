/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wcslen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 22:17:41 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/05 00:04:13 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "libft.h"

/*
** check how long a wchar_t string is
*/

size_t	ft_wcslen(wchar_t *ws)
{
	const wchar_t *ws_orig = ws;

	while (*ws)
		ws++;
	return ((size_t)ws - (size_t)ws_orig);
}
