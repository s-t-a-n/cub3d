/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 18:57:04 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 17:39:26 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_raycast *raycast, t_cub3d *cub3d)
{
	double		lineheight;
	t_vector2	pos;

	lineheight = WALL_SIZE_MP * ((double)cub3d->mlx->resolution.y
					/ raycast->distance);
	pos.y = ((double)(cub3d->mlx->resolution.y / 2.0)) - (lineheight / 2.0);
	if (pos.y < 0)
		pos.y = 0;
	pos.x = raycast->phaser.x;
	draw_textured_line(raycast, cub3d, pos, lineheight);
}

void	swap_sprites(t_raycast *raycast, int a, int b)
{
	t_sprite tmp;

	tmp = raycast->sprites[a];
	raycast->sprites[a] = raycast->sprites[b];
	raycast->sprites[b] = tmp;
}

int		playerdistance_sprites(t_player *player, t_flvector2 pos)
{
	return (fabs(player->pos.x - pos.x) +
				fabs(player->pos.y - pos.y));
}

void	update_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < raycast->spritecount)
	{
		sprite = &raycast->sprites[i];
		sprite->distance = playerdistance_sprites(cub3d->player, sprite->pos);
		i++;
	}
}

void	sort_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int		i;
	t_bool	changed;

	update_sprites(raycast, cub3d);
	changed = true;
	while (changed)
	{
		changed = false;
		i = 0;
		while (i + 1 < raycast->spritecount)
		{
			if (raycast->sprites[i].distance
					< raycast->sprites[i + 1].distance)
			{
				swap_sprites(raycast, i, i + 1);
				changed = true;
			}
			i++;
		}
	}
}
