/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_rendering.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 19:59:13 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 16:48:28 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

void	clear_image(t_mlx *mlx)
{
	t_vector2 pos;

	pos.x = 0;
	pos.y = 0;
	mlx_wrect(mlx->image_nact, pos, mlx->resolution, 0x00000000);
}

void	swap_image_buffers(t_mlx *mlx)
{
	if (mlx->image_nact_i == IMAGE_COUNT - 1)
	{
		mlx->image_nact_i = 0;
		mlx->image_nact = &mlx->images[0];
		mlx->image_act = &mlx->images[IMAGE_COUNT - 1];
	}
	else
	{
		mlx->image_act = &mlx->images[mlx->image_nact_i];
		mlx->image_nact_i++;
		mlx->image_nact = &mlx->images[mlx->image_nact_i];
	}
}

int		render_frame(t_cub3d *cub3d)
{
	raycaster(cub3d->raycast, cub3d);
	swap_image_buffers(cub3d->mlx);
	if (cub3d->save_frame)
		exit(1 ^ write_bmp_from_mlx_image(cub3d->mlx->image_act, SAVE_FILE));
	mlx_put_image_to_window(cub3d->mlx->backend, cub3d->mlx->window,
			cub3d->mlx->image_act->img, 0, 0);
	return (noerr);
}
