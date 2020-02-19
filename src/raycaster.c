/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 23:39:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/18 18:12:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_pos_in_cameraplane(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->campos.y = 0.0; //vertical raycasting is not implemented 
	raycast->campos.x = 2.0 * raycast->phaser.x / cub3d->mlx->resolution.x - 1;
}

void	calc_ray_position_and_direction(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->pos.x = (int)cub3d->player->pos.x;
	raycast->pos.y = (int)cub3d->player->pos.y;
	raycast->dir.x = cub3d->player->vdir.x + raycast->camplane.x * raycast->campos.x;
	raycast->dir.y = cub3d->player->vdir.y + raycast->camplane.y * raycast->campos.x;
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

void	calc_delta_intercept(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->delta_intercept.x = raycast->dir.x == 0.0 ? 0.0 : fabs(1.0 / raycast->dir.x);
	raycast->delta_intercept.y = raycast->dir.y == 0.0 ? 0.0 : fabs(1.0 / raycast->dir.y);
	cub3d = NULL;
}

void	calc_distance(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->side == 0)
	{
		raycast->distance = (raycast->pos.x - cub3d->player->pos.x + (1 - raycast->tilestep.x) / 2) / raycast->dir.x;
	}
	else
	{
		raycast->distance = (raycast->pos.y - cub3d->player->pos.y + (1 - raycast->tilestep.y) / 2) / raycast->dir.y;
	}
}

void		perform_dda(t_raycast *raycast, t_cub3d *cub3d)
{
	while(!raycast->hit)
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
		if (cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x] != MAP_WALKABLE)
			raycast->hit = true;
	}
}


void		draw_line(t_raycast *raycast, t_cub3d *cub3d)
{
	float lineheight;
	t_vector2 pos;
	t_vector2 size;
	
	lineheight = 1.2 * (cub3d->mlx->resolution.y / raycast->distance);

	if (lineheight - (long)lineheight > 0.5)
		lineheight += 0.5;
	if (lineheight > cub3d->mlx->resolution.y)
		lineheight = cub3d->mlx->resolution.y;

	pos.y = (cub3d->mlx->resolution.y / 2) - (lineheight / 2);
	pos.x = raycast->phaser.x;
	size.y = (int)lineheight;
	size.x = 1;
	if (raycast->side)
		mlx_wrect(*(cub3d->mlx->image_nact), pos, size, 0x00C74D0F);
	else
		mlx_wrect(*(cub3d->mlx->image_nact), pos, size, 0x00A9410D);
}

#include "unistd.h"

t_bool	raycaster(t_raycast *raycast, t_cub3d *cub3d)
{
	init_raycast(raycast, cub3d);
	while (raycast->phaser.x < cub3d->mlx->resolution.x)
	{
		raycast->hit = false;
		calc_pos_in_cameraplane(raycast, cub3d);
		calc_ray_position_and_direction(raycast, cub3d);
		calc_tilestep_and_intercept(raycast, cub3d);
		calc_delta_intercept(raycast, cub3d);
		perform_dda(raycast, cub3d);
		calc_distance(raycast, cub3d);
		//cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x] = '*';
		draw_line(raycast, cub3d);
		(raycast->phaser.x)++;
	}
	//dump_scenedata_map(cub3d->scenedata);
	return (noerr);
}
