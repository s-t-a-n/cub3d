/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_keyhandling1.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:19:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:20:38 by sverschu      ########   odam.nl         */
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
