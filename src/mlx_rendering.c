/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_rendering.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 19:59:13 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/02 12:47:06 by sverschu      ########   odam.nl         */
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
	//draw_colored_floors_and_ceiling(cub3d->mlx, cub3d->scenedata);
	//draw_textured_floor_and_ceiling(cub3d->raycast, cub3d);
	//clear_image(cub3d->mlx);
	raycaster(cub3d->raycast, cub3d);
	//if (cub3d->mlx->image_act == &cub3d->mlx->image_b)
	//{
	//	cub3d->mlx->image_act = &cub3d->mlx->image_a;
	//	cub3d->mlx->image_nact = &cub3d->mlx->image_c;
	//}
	//else if (cub3d->mlx->image_act == &cub3d->mlx->image_a)
	//{
	//	cub3d->mlx->image_act = &cub3d->mlx->image_c;
	//	cub3d->mlx->image_nact = &cub3d->mlx->image_b;
	//}
	//else if (cub3d->mlx->image_act == &cub3d->mlx->image_c)
	//{
	//	cub3d->mlx->image_act = &cub3d->mlx->image_b;
	//	cub3d->mlx->image_nact = &cub3d->mlx->image_a;
	//}
	//ft_pswap((void **)&cub3d->mlx->image_act, (void **)&cub3d->mlx->image_nact);
	//mlx_clear_window(cub3d->mlx->backend, cub3d->mlx->window);
	swap_image_buffers(cub3d->mlx);
	mlx_put_image_to_window(cub3d->mlx->backend, cub3d->mlx->window,
			cub3d->mlx->image_act->img, 0, 0);
	return (noerr);
}
