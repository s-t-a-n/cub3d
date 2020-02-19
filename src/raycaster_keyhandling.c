/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_keyhandling.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:08:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/18 18:47:21 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Thank you Lode
*/

void	move_forward(t_raycast *raycast, t_cub3d *cub3d)
{
	if (cub3d->scenedata->map->mem[(int)(cub3d->player->pos.y + COLLISION_WALL_MP * cub3d->player->vdir.y * cub3d->player->mov_speed)][(int)(cub3d->player->pos.x + COLLISION_WALL_MP * cub3d->player->vdir.x * cub3d->player->mov_speed)] == MAP_WALKABLE)
	{
		cub3d->player->pos.x += cub3d->player->vdir.x * cub3d->player->mov_speed;
		cub3d->player->pos.y += cub3d->player->vdir.y * cub3d->player->mov_speed;
	}
	else if (cub3d->scenedata->map->mem[(int)(cub3d->player->pos.y  +  COLLISION_WALL_MP * (cub3d->player->vdir.y + COLLISION_WALL_SLIDE) * cub3d->player->mov_speed)][(int)(cub3d->player->pos.x + COLLISION_WALL_MP * (cub3d->player->vdir.x + COLLISION_WALL_SLIDE) * cub3d->player->mov_speed)] == MAP_WALKABLE)
	{
		cub3d->player->pos.x += (cub3d->player->vdir.x + COLLISION_WALL_SLIDE) * cub3d->player->mov_speed;
		cub3d->player->pos.y += (cub3d->player->vdir.y + COLLISION_WALL_SLIDE) * cub3d->player->mov_speed;
	}
	else if (cub3d->scenedata->map->mem[(int)(cub3d->player->pos.y  +  COLLISION_WALL_MP * (cub3d->player->vdir.y - COLLISION_WALL_SLIDE) * cub3d->player->mov_speed)][(int)(cub3d->player->pos.x + COLLISION_WALL_MP * (cub3d->player->vdir.x - COLLISION_WALL_SLIDE) * cub3d->player->mov_speed)] == MAP_WALKABLE)
	{
		cub3d->player->pos.x += (cub3d->player->vdir.x - COLLISION_WALL_SLIDE) * cub3d->player->mov_speed;
		cub3d->player->pos.y += (cub3d->player->vdir.y - COLLISION_WALL_SLIDE) * cub3d->player->mov_speed;
	}
	raycast = NULL;
}

void	move_left(t_cub3d *cub3d)
{
		cub3d->player->pos.x -= (cub3d->player->vdir.x * cos(90) - cub3d->player->vdir.y * sin(90)) * cub3d->player->mov_speed;
		cub3d->player->pos.y -= (cub3d->player->vdir.y * cos(90) + cub3d->player->vdir.x * sin(90)) * cub3d->player->mov_speed;
}

void	move_right(t_cub3d *cub3d)
{
		cub3d->player->pos.x += (cub3d->player->vdir.x * cos(90) - cub3d->player->vdir.y * sin(90)) * cub3d->player->mov_speed;
		cub3d->player->pos.y += (cub3d->player->vdir.y * cos(90) + cub3d->player->vdir.x * sin(90)) * cub3d->player->mov_speed;
}

void	move_backward(t_raycast *raycast, t_cub3d *cub3d)
{
	if (cub3d->scenedata->map->mem[(int)(cub3d->player->pos.y - COLLISION_WALL_MP * cub3d->player->vdir.y * cub3d->player->mov_speed)][(int)(cub3d->player->pos.x - COLLISION_WALL_MP * cub3d->player->vdir.x * cub3d->player->mov_speed)] == MAP_WALKABLE)
	{
		cub3d->player->pos.x -= cub3d->player->vdir.x * cub3d->player->mov_speed;
		cub3d->player->pos.y -= cub3d->player->vdir.y * cub3d->player->mov_speed;
	}
	raycast = NULL;
}

void	rotate_left(t_raycast *raycast, t_cub3d *cub3d)
{
	float oldDirX = cub3d->player->vdir.x;
	cub3d->player->vdir.x = cub3d->player->vdir.x * cos(-cub3d->player->rot_speed) - cub3d->player->vdir.y * sin(-cub3d->player->rot_speed);
	cub3d->player->vdir.y = oldDirX * sin(-cub3d->player->rot_speed) + cub3d->player->vdir.y * cos(-cub3d->player->rot_speed);
	
	float oldPlaneX = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(-cub3d->player->rot_speed) - raycast->camplane.y * sin(-cub3d->player->rot_speed);
	raycast->camplane.y = oldPlaneX * sin(-cub3d->player->rot_speed) + raycast->camplane.y * cos(-cub3d->player->rot_speed);
}

void	rotate_right(t_raycast *raycast, t_cub3d *cub3d)
{
	float oldDirX = cub3d->player->vdir.x;
	cub3d->player->vdir.x = cub3d->player->vdir.x * cos(cub3d->player->rot_speed) - cub3d->player->vdir.y * sin(cub3d->player->rot_speed);
	cub3d->player->vdir.y = oldDirX * sin(cub3d->player->rot_speed) + cub3d->player->vdir.y * cos(cub3d->player->rot_speed);

	float oldPlaneX = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(cub3d->player->rot_speed) - raycast->camplane.y * sin(cub3d->player->rot_speed);
	raycast->camplane.y = oldPlaneX * sin(cub3d->player->rot_speed) + raycast->camplane.y * cos(cub3d->player->rot_speed);
}

