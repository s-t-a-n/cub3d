/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_keyhandling.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:08:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/17 19:50:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Thank you Lode
*/

void	move_forward(t_raycast *raycast, t_cub3d *cub3d)
{
	//printf("old player pos : %f by %f\n",cub3d->player->pos.x, cub3d->player->pos.y);
	cub3d->player->pos.x += cub3d->player->vdir.x * raycast->mov_speed;
	cub3d->player->pos.y += cub3d->player->vdir.y * raycast->mov_speed;
	//printf("new player pos : %f by %f\n",cub3d->player->pos.x, cub3d->player->pos.y);
}

void	move_backward(t_raycast *raycast, t_cub3d *cub3d)
{
	cub3d->player->pos.x -= cub3d->player->vdir.x * raycast->mov_speed;
	cub3d->player->pos.y -= cub3d->player->vdir.y * raycast->mov_speed;
}

void	rotate_left(t_raycast *raycast, t_cub3d *cub3d)
{
	double oldDirX = cub3d->player->vdir.x;
	cub3d->player->vdir.x = cub3d->player->vdir.x * cos(-raycast->rot_speed) - cub3d->player->vdir.y * sin(-raycast->rot_speed);
	cub3d->player->vdir.y = oldDirX * sin(-raycast->rot_speed) + cub3d->player->vdir.y * cos(-raycast->rot_speed);
	
	double oldPlaneX = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(-raycast->rot_speed) - raycast->camplane.y * sin(-raycast->rot_speed);
	raycast->camplane.y = oldPlaneX * sin(-raycast->rot_speed) + raycast->camplane.y * cos(-raycast->rot_speed);
}

void	rotate_right(t_raycast *raycast, t_cub3d *cub3d)
{
	double oldDirX = cub3d->player->vdir.x;
	cub3d->player->vdir.x = cub3d->player->vdir.x * cos(raycast->rot_speed) - cub3d->player->vdir.y * sin(raycast->rot_speed);
	cub3d->player->vdir.y = oldDirX * sin(raycast->rot_speed) + cub3d->player->vdir.y * cos(raycast->rot_speed);

	double oldPlaneX = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(raycast->rot_speed) - raycast->camplane.y * sin(raycast->rot_speed);
	raycast->camplane.y = oldPlaneX * sin(raycast->rot_speed) + raycast->camplane.y * cos(raycast->rot_speed);
}

