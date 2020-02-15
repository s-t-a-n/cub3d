/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_rendering.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 19:59:13 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 18:54:16 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_mlx *mlx)
{
	t_vector2 pos;

	pos.x = 0;
	pos.y = 0;

	mlx_wrect(mlx->image_act == &mlx->image_a ? mlx->image_b : mlx->image_a,
			pos, mlx->resolution, 0xFFFFFFFF);
}

#include <unistd.h>

int		render_frame(t_cub3d *cub3d)
{
	sleep (1);
	return(raycaster(cub3d));
}
