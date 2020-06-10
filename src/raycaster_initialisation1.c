/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_initialisation1.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:11:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:11:44 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				insert_sprite(t_raycast *raycast, int x, int y, int item)
{
	t_sprite sprite;

	sprite.pos.x = x + 0.5;
	sprite.pos.y = y + 0.5;
	sprite.item = item;
	raycast->sprites[raycast->spritecount] = sprite;
	raycast->spritecount++;
}
