/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_generic.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 20:01:32 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/12 20:33:51 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** get TRGB formatted colorcode
*/

unsigned int    trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

/*
**	closes down program (as hook)
*/
int			shutdown(int code, void *ptr)
{
	exit(0);
	return (code > (int)ptr);
}
