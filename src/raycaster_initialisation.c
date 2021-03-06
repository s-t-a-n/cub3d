/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_initialisation.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 19:40:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 19:09:18 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_flvector2	vectorize_edirection(t_direction dir)
{
	t_flvector2	vdir;

	if (dir == north)
	{
		vdir.x = 0;
		vdir.y = -1;
	}
	else if (dir == east)
	{
		vdir.x = 1;
		vdir.y = 0;
	}
	else if (dir == south)
	{
		vdir.x = 0;
		vdir.y = 1;
	}
	else
	{
		vdir.x = -1;
		vdir.y = 0;
	}
	return (vdir);
}

static t_flvector2	calculate_initial_camplane(t_direction dir)
{
	t_flvector2 camplane;

	if (dir == north)
	{
		camplane.x = VW_ANGLE;
		camplane.y = 0.0;
	}
	else if (dir == east)
	{
		camplane.x = 0.0;
		camplane.y = VW_ANGLE;
	}
	else if (dir == south)
	{
		camplane.x = -VW_ANGLE;
		camplane.y = 0.0;
	}
	else
	{
		camplane.x = 0.0;
		camplane.y = -VW_ANGLE;
	}
	return (camplane);
}

void				setup_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int				y;
	int				x;
	unsigned char	*s;

	raycast->spritecount = 0;
	raycast->sprite_update = 0;
	y = 0;
	while (y < (int)cub3d->scenedata->map->element_count)
	{
		s = cub3d->scenedata->map->mem[y];
		x = 0;
		while (s[x])
		{
			if (s[x] == MAP_ITEM_WALKABLE)
				insert_sprite(raycast, x, y, s[x]);
			x++;
		}
		y++;
	}
}

void				first_init_raycast(t_raycast *raycast, t_cub3d *cub3d)
{
	cub3d->player->vdir =
		vectorize_edirection(cub3d->scenedata->player_orientation);
	cub3d->player->pos.x += 0.5;
	cub3d->player->pos.y += 0.5;
	raycast->camplane = calculate_initial_camplane(
			cub3d->scenedata->player_orientation);
	setup_sprites(raycast, cub3d);
}

void				init_raycast(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->phaser.x = 0;
	raycast->phaser.y = 0;
	if (cub3d->first_render)
	{
		first_init_raycast(raycast, cub3d);
		cub3d->first_render = FALSE;
	}
}
