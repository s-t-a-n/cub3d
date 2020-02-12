/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_meta.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 00:13:33 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 00:21:58 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_edirection_to_flvector2(t_direction dir, t_flvector2 *vdir)
{
	if (dir == north)
	{
		vdir->x = 0;
		vdir->y = 0;
	}
	else if (dir == east)
	{
		vdir->x = 0;
		vdir->y = 0;
	}
	else if (dir == south)
	{
		vdir->x = 0;
		vdir->y = 0;
	}
	else
	{
		vdir->x = 0;
		vdir->y = 0;
	}
}
