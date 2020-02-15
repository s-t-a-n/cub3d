/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 23:39:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/15 20:42:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
t_vector2 calc_tilestep(t_player *player)
{
	t_vector2 tilestep;

	if (player->dir.y > 0 && player->dir.x > 0)
	{
		//right upper quadrant
		tilestep.x = 1;
		tilestep.y = 1;
	}
	else if (player->dir.y < 0 && player->dir.x > 0)
	{
		//right lower quadrant
		tilestep.x = 1;
		tilestep.y = -1;
	}
	else if (player->dir.y < 0 && player->dir.x < 0)
	{
		// left lower quadrant
		tilestep.x = -1;
		tilestep.y = -1;
	}
	else if (player->dir.y < 0 && player->dir.x > 0)
	{
		// left upper quadrant
		tilestep.x = -1;
		tilestep.y = 1;
	}
	else
	{
		tilestep.x = 0;
		tilestep.y = 0;
	}
	return(tilestep);
}
*/

void	calc_camera_plane_and_pos_in_plane(t_raycast *raycast, t_cub3d *cub3d)
{
//	raycast->camplane.x = -0.66;
//	raycast->camplane.y = 0.0; // calc this later
	raycast->campos.y = 0.0; //vertical raycasting is not implemented 
	raycast->campos.x = 2.0 * raycast->phaser.x / cub3d->mlx->resolution.x - 1.0;
}

void	calc_ray_position_and_direction(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->pos.x = cub3d->player->pos.x;
	raycast->pos.y = cub3d->player->pos.y;
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
		raycast->intercept.x = (cub3d->player->pos.x + 1.0 - raycast->pos.x) * raycast->delta_intercept.x;
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
		raycast->intercept.y = (cub3d->player->pos.y + 1.0 - raycast->pos.y) * raycast->delta_intercept.y;
	}
}

void	calc_delta_intercept(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->delta_intercept.x = raycast->dir.x == 0.0 ? 0.0 : fabs(1 / raycast->dir.x);
	raycast->delta_intercept.y = raycast->dir.y == 0.0 ? 0.0 : fabs(1 / raycast->dir.y);
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

/*
float		calc_line_height()
{

}
*/

void		perform_dda(t_cub3d *cub3d, t_raycast *raycast)
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
		if (cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x] != 'X')
			raycast->hit = true;
	}
}


void		draw_line(t_raycast *raycast, t_cub3d *cub3d)
{
	float lineheight = (float)cub3d->mlx->resolution.y / raycast->distance;

	printf("lineheight : %f\n", lineheight);
	t_vector2 pos;

	pos.y = (cub3d->mlx->resolution.y / 2) - ((int)lineheight / 2);
	pos.x = raycast->phaser.x;

	t_vector2 size;

	size.y = (int)lineheight;
	size.x = 1;
	//printf("pos.y: %i\n", pos.y);
	mlx_wrect(*(cub3d->mlx->image_act), pos, size, 0x00FFFFFF);
	//return;
	size.x = 10;
	size.y = 10;
	pos.x = 10;
	pos.y = 10;
	//pos.x = (cub3d->mlx->resolution.x / 2) - size.x;
	//pos.y = (cub3d->mlx->resolution.y / 2) - size.y;
	//mlx_wrect(*(cub3d->mlx->image_act), pos, size, 0x00FFFFFF);

	mlx_put_image_to_window(cub3d->mlx->backend, cub3d->mlx->window, cub3d->mlx->image_act->img, 0, 0);

}



#include "unistd.h"

t_bool	raycaster(t_cub3d *cub3d)
{
	t_raycast	raycast;

	init_raycast(&raycast, cub3d);
	while (raycast.phaser.x < cub3d->mlx->resolution.x)
	{
		raycast.hit = false;
		calc_camera_plane_and_pos_in_plane(&raycast, cub3d);
		calc_ray_position_and_direction(&raycast, cub3d);
		calc_tilestep_and_intercept(&raycast, cub3d);
		calc_delta_intercept(&raycast, cub3d);
		//printf("intercept: %f x %f\n", raycast.intercept.x, raycast.intercept.y);
		//printf("dir: %f x %f\n", raycast.dir.x, raycast.dir.y);
		//printf("vdir: %f x %f\n", cub3d->player->vdir.x, cub3d->player->vdir.y);
		perform_dda(cub3d, &raycast);
		calc_distance(&raycast, cub3d);
		//printf("distance: %f\n", raycast.distance);
		cub3d->scenedata->map->mem[raycast.pos.y][raycast.pos.x] = '*';
		draw_line(&raycast, cub3d);
		//printf("this is where we draw! for box: %i x %i\n", raycast.pos.x, raycast.pos.y);
		(raycast.phaser.x)++;
		//sleep (1);
	}
		dump_scenedata_map(cub3d->scenedata);
	mlx_put_image_to_window(cub3d->mlx->backend, cub3d->mlx->window, cub3d->mlx->image_act->img, 0, 0);
	return (false);
}
