/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_keyhandling.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:08:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/20 18:34:22 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Thank you Lode, Jesus of Raycasting
*/

void	move_forward(char **map, t_player *player)
{
	if (map[(int)(player->pos.y + player->vdir.y * player->mov_speed
				* COLLISION_WALL_MP)][(int)player->pos.x] == MAP_WALKABLE)
		player->pos.y += player->vdir.y * player->mov_speed;
	if (map[(int)player->pos.y][(int)(player->pos.x + player->vdir.x
				* player->mov_speed * COLLISION_WALL_MP)] == MAP_WALKABLE) 
		player->pos.x += player->vdir.x * player->mov_speed;
}

void	move_backward(char **map, t_player *player)
{
	if (map[(int)(player->pos.y - player->vdir.y * player->mov_speed
				* COLLISION_WALL_MP)][(int)player->pos.x] == MAP_WALKABLE)
		player->pos.y -= player->vdir.y * player->mov_speed;
	if (map[(int)player->pos.y][(int)(player->pos.x - player->vdir.x *
				player->mov_speed * COLLISION_WALL_MP)] == MAP_WALKABLE)
		player->pos.x -= player->vdir.x * player->mov_speed;
}

void	move_left(char **map, t_player *player)
{
	if (map[(int)(player->pos.y)][(int)(player->pos.x + player->vdir.y *
				player->mov_speed)] == MAP_WALKABLE)
		player->pos.x += player->vdir.y * player->mov_speed;
	if (map[(int)(player->pos.y + -player->vdir.x * player->mov_speed *
				COLLISION_WALL_MP)][(int)(player->pos.x)] == MAP_WALKABLE)
		player->pos.y += -player->vdir.x * player->mov_speed;
}

void	move_right(char **map, t_player *player)
{
	if (map[(int)(player->pos.y)][(int)(player->pos.x + -player->vdir.y *
				player->mov_speed)] == MAP_WALKABLE)
		player->pos.x += -player->vdir.y * player->mov_speed;
	if (map[(int)(player->pos.y + player->vdir.x * player->mov_speed * 
				COLLISION_WALL_MP)][(int)(player->pos.x)] == MAP_WALKABLE)
		player->pos.y += player->vdir.x * player->mov_speed;
}

void	rotate_left(t_raycast *raycast, t_player *player)
{
	double old_vdir_x;
	double old_camplane_x;

	old_vdir_x = player->vdir.x;
	player->vdir.x = player->vdir.x * cos(-player->rot_speed) - player->vdir.y
		* sin(-player->rot_speed);
	player->vdir.y = old_vdir_x * sin(-player->rot_speed) + player->vdir.y
		* cos(-player->rot_speed);
	old_camplane_x = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(-player->rot_speed)
		- raycast->camplane.y * sin(-player->rot_speed);
	raycast->camplane.y = old_camplane_x * sin(-player->rot_speed)
		+ raycast->camplane.y * cos(-player->rot_speed);
}

void	rotate_right(t_raycast *raycast, t_player *player)
{
	double old_vdir_x;
	double old_camplane_x;

	old_vdir_x = player->vdir.x;
	player->vdir.x = player->vdir.x * cos(player->rot_speed) - player->vdir.y
		* sin(player->rot_speed);
	player->vdir.y = old_vdir_x * sin(player->rot_speed) + player->vdir.y
		* cos(player->rot_speed);
	old_camplane_x = raycast->camplane.x;
	raycast->camplane.x = raycast->camplane.x * cos(player->rot_speed)
		- raycast->camplane.y * sin(player->rot_speed);
	raycast->camplane.y = old_camplane_x * sin(player->rot_speed)
		+ raycast->camplane.y * cos(player->rot_speed);
}

