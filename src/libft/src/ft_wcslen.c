/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wcslen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 22:02:07 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 22:02:09 by sverschu      ########   odam.nl         */
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
