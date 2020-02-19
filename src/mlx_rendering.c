/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_rendering.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 19:59:13 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/19 21:10:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_mlx *mlx)
{
	t_vector2 pos;

	pos.x = 0;
	pos.y = 0;

	mlx_wrect(mlx->image_nact, pos, mlx->resolution, 0x00000000);
}

void	draw_colored_floors_and_ceiling(t_mlx *mlx, t_scenedata *scenedata)
{
	t_vector2 pos;
	t_vector2 size;

	size.x = mlx->resolution.x;
	size.y = mlx->resolution.y / 2;
	pos.x = 0;
	pos.y = 0;
	mlx_wrect(mlx->image_nact, pos, size, scenedata->ceiling_trgb);
	pos.x = 0;
	pos.y += size.y;
	mlx_wrect(mlx->image_nact, pos, size, scenedata->floor_trgb);
}

int		render_frame(t_cub3d *cub3d)
{
	//clear_image(cub3d->mlx);
	draw_colored_floors_and_ceiling(cub3d->mlx, cub3d->scenedata);
	raycaster(cub3d->raycast, cub3d);
	ft_pswap((void **)&cub3d->mlx->image_act, (void **)&cub3d->mlx->image_nact);
	mlx_put_image_to_window(cub3d->mlx->backend, cub3d->mlx->window, cub3d->mlx->image_act->img, 0, 0);
	return (noerr);
}
