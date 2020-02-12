/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 23:39:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 00:19:37 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	raycaster(t_mlx *mlx, t_player *player)
{
	float	ang_ctr;

	ang_ctr = VW_ANGLE;
	while (ang_ctr > 0.0)
	{
		
		ang_ctr -= VW_ANGLE_INC;
	}
}
