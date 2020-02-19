/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 23:39:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/19 21:52:32 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_pos_in_cameraplane(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->campos.y = 0.0; //vertical raycasting is not implemented 
	raycast->campos.x = 2.0 * raycast->phaser.x / cub3d->mlx->resolution.x - 1;
}

void	calc_ray_position_and_direction(t_raycast *raycast, t_player *player)
{
	raycast->pos.x = (int)player->pos.x;
	raycast->pos.y = (int)player->pos.y;
	raycast->dir.x = player->vdir.x + raycast->camplane.x * raycast->campos.x;
	raycast->dir.y = player->vdir.y + raycast->camplane.y * raycast->campos.x;
}

void	calc_tilestep_and_intercept(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->dir.x < 0)
	{
		//left quadrants
		raycast->tilestep.x = -1;
		raycast->intercept.x = (cub3d->player->pos.x - raycast->pos.x) * raycast->delta_intercept.x;
	}
	else
	{
		//right quadrants
		raycast->tilestep.x = 1;
		raycast->intercept.x = (raycast->pos.x + 1 - cub3d->player->pos.x) * raycast->delta_intercept.x;
	}
	if (raycast->dir.y < 0)
	{
		//upper quadrants
		raycast->tilestep.y = -1;
		raycast->intercept.y = (cub3d->player->pos.y - raycast->pos.y) * raycast->delta_intercept.y;
	}
	else
	{
		//lower quadrants
		raycast->tilestep.y = 1;
		raycast->intercept.y = (raycast->pos.y + 1 - cub3d->player->pos.y) * raycast->delta_intercept.y;
	}
}

void	calc_delta_intercept(t_raycast *raycast)
{
	raycast->delta_intercept.x = fabs(1.0 / raycast->dir.x);
	raycast->delta_intercept.y = fabs(1.0 / raycast->dir.y);
}

void	calc_distance(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->side == 0)
		raycast->distance = (raycast->pos.x - cub3d->player->pos.x + (1 - raycast->tilestep.x) / 2.0) / raycast->dir.x;
	else
		raycast->distance = (raycast->pos.y - cub3d->player->pos.y + (1 - raycast->tilestep.y) / 2.0) / raycast->dir.y;
	//printf("distance: %f\n", raycast->distance);
}

void		perform_dda(t_raycast *raycast, t_cub3d *cub3d)
{
	while(!raycast->hit)
	{
		if (raycast->intercept.x <= raycast->intercept.y)
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
		raycast->item = cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x];
		if (raycast->item != MAP_WALKABLE)
			raycast->hit = true;
	}
}

void		draw_colored_line(t_raycast *raycast, t_cub3d *cub3d,
				t_vector2 pos, t_vector2 size)
{
	if (raycast->side)
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00C74D0F);
	else
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00A9410D);
}

/*
void		draw_textured_line(t_raycast *raycast, t_cub3d *cub3d, t_vector2 pos, t_vector2 size, double lineheight)
{
	cub3d = NULL;
	raycast = NULL;
}
*/
void		draw_line(t_raycast *raycast, t_cub3d *cub3d)
{
	double lineheight;
	t_vector2 pos;
	t_vector2 size;
	
	lineheight = WALL_SIZE_MP * ((double)cub3d->mlx->resolution.y / raycast->distance);
//	if ((long)lineheight - lineheight > 0.5)
//		lineheight += 0.2;
	if (lineheight > cub3d->mlx->resolution.y)
		lineheight = cub3d->mlx->resolution.y;
	pos.y = ((double)(cub3d->mlx->resolution.y / 2.0)) - (lineheight / 2.0);
	pos.x = raycast->phaser.x;
	size.y = lineheight;
	size.x = 1;
	//draw_textured_line(raycast, cub3d, pos, size, lineheight);
	draw_colored_line(raycast, cub3d, pos, size);
}

t_bool	raycaster(t_raycast *raycast, t_cub3d *cub3d)
{
	init_raycast(raycast, cub3d);
	while (raycast->phaser.x < cub3d->mlx->resolution.x)
	{
		raycast->hit = false;
		calc_pos_in_cameraplane(raycast, cub3d);
		calc_ray_position_and_direction(raycast, cub3d->player);
		calc_tilestep_and_intercept(raycast, cub3d);
		calc_delta_intercept(raycast);
		perform_dda(raycast, cub3d);
		calc_distance(raycast, cub3d);
		//cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x] = '*';
		draw_line(raycast, cub3d);
		(raycast->phaser.x)++;
	}
	//dump_scenedata_map(cub3d->scenedata);
	return (noerr);
}
