/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster4.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:00:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 17:47:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				calc_distance(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->side == 0)
		raycast->distance = (raycast->pos.x - cub3d->player->pos.x
				+ (1 - raycast->tilestep.x) / 2.0) / raycast->dir.x;
	else
		raycast->distance = (raycast->pos.y - cub3d->player->pos.y
				+ (1 - raycast->tilestep.y) / 2.0) / raycast->dir.y;
	raycast->zbuffer[raycast->phaser.x] = raycast->distance;
}

void				perform_dda(t_raycast *raycast, t_cub3d *cub3d)
{
	while (!raycast->hit)
	{
		if (raycast->intercept.x < raycast->intercept.y)
		{
			raycast->intercept.x += raycast->delta_intercept.x;
			raycast->pos.x += raycast->tilestep.x;
			raycast->side = 0;
		}
		else
		{
			raycast->intercept.y += raycast->delta_intercept.y;
			raycast->pos.y += raycast->tilestep.y;
			raycast->side = 1;
		}
		raycast->item = cub3d->scenedata->map->mem[raycast->pos.y]
			[raycast->pos.x];
		if (raycast->item != MAP_WALKABLE
				&& raycast->item != MAP_ITEM_WALKABLE)
			raycast->hit = true;
	}
}

int					select_texture_for_wall(t_raycast *raycast)
{
	if (raycast->dir.y >= 0 && raycast->side)
		return (TEXT_N);
	else if (raycast->dir.y < 0 && raycast->side)
		return (TEXT_S);
	else if (raycast->dir.x >= 0 && raycast->side == 0)
		return (TEXT_W);
	else if (raycast->dir.x < 0 && raycast->side == 0)
		return (TEXT_E);
	else
	{
		crit_error("raycast:", "unknown texture!", NULL);
		return (-1);
	}
}

t_mlx_text_image	*select_texture(t_cub3d *cub3d, t_raycast *raycast,
						int num)
{
	if (num == MAP_WALL)
		return (&cub3d->mlx->textures[select_texture_for_wall(raycast)]);
	else if (num == MAP_ITEM_WALKABLE)
		return (&cub3d->mlx->textures[TEXT_SP]);
	else
		return (NULL);
}

void				draw_colored_floors_and_ceiling(t_mlx *mlx,
						t_scenedata *scenedata)
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
