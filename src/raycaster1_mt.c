/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 18:54:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 18:16:39 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include <pthread.h>
#include "cub3d.h"

void		draw_sprites_norm2(t_raycast *raycast, t_cub3d *cub3d,
			t_draw_sprite *s)
{
	while (s->y < s->drawendy)
	{
		s->d = (s->y) * 256 - cub3d->scenedata->resolution.y
			* 128 + s->spriteheight * 128;
		s->texy = ((s->d * s->texture->size.y) / s->spriteheight) / 256;
		s->pos.x = s->x;
		s->pos.y = s->y;
		s->tex_pos.x = s->texx;
		s->tex_pos.y = s->texy;
		s->tex_pos.y = s->tex_pos.y < 0 ? 0 : s->tex_pos.y;
		s->tex_pos.y = s->tex_pos.y > s->texture->size.y ? s->texture->size.y
			: s->tex_pos.y;
		s->tex_pos.x = s->tex_pos.x < 0 ? 0 : s->tex_pos.x;
		s->tex_pos.x = s->tex_pos.x > s->texture->size.x ? s->texture->size.x
			: s->tex_pos.x;
		s->color = mlx_rpixel(s->tex_pos, s->texture);
		if (s->color != 0x00000000 && (s->color ^ 0xFF000000))
			mlx_wpixel(cub3d->mlx->image_nact, s->pos, s->color);
		s->y++;
	}
	(void)raycast;
}

void		draw_sprites_norm1(t_raycast *raycast, t_cub3d *cub3d,
			t_draw_sprite *s)
{
	s->x = s->drawstartx;
	while (s->x < s->drawendx)
	{
		s->texx = (int)(256 * (s->x - (-s->spritewidth / 2 + s->spritescreenx))
			* s->texture->size.x / s->spritewidth) / 256;
		if (s->transformy > 0 && s->x > 0 && s->x <
			cub3d->scenedata->resolution.x
			&& s->transformy < raycast->zbuffer[s->x])
		{
			s->y = s->drawstarty;
			draw_sprites_norm2(raycast, cub3d, s);
		}
		s->x++;
	}
}

void		draw_sprites_norm0(t_raycast *raycast, t_cub3d *cub3d,
			t_draw_sprite *s)
{
	s->spritex = raycast->sprites[s->i].pos.x - cub3d->player->pos.x;
	s->spritey = raycast->sprites[s->i].pos.y - cub3d->player->pos.y;
	s->invdet = 1.0 / (raycast->camplane.x * cub3d->player->vdir.y
			- cub3d->player->vdir.x * raycast->camplane.y);
	s->transformx = s->invdet * (cub3d->player->vdir.y * s->spritex
			- cub3d->player->vdir.x * s->spritey);
	s->transformy = s->invdet * (-raycast->camplane.y * s->spritex
			+ raycast->camplane.x * s->spritey);
	s->spritescreenx = (int)((cub3d->scenedata->resolution.x / 2)
			* (1 + s->transformx / s->transformy));
	s->spriteheight = abs((int)(cub3d->scenedata->resolution.y
				/ (s->transformy))) * 0.8;
	s->drawstarty = -s->spriteheight / 2
		+ cub3d->scenedata->resolution.y / 2;
}

void		draw_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	t_draw_sprite		s;

	s.texture = select_texture(cub3d, raycast, MAP_ITEM_WALKABLE);
	s.i = 0;
	while (s.i < raycast->spritecount)
	{
		draw_sprites_norm0(raycast, cub3d, &s);
		if (s.drawstarty < 0)
			s.drawstarty = 0;
		s.drawendy = s.spriteheight / 2 + cub3d->scenedata->resolution.y / 2;
		if (s.drawendy >= cub3d->scenedata->resolution.y)
			s.drawendy = cub3d->scenedata->resolution.y - 1;
		s.spritewidth = abs((int)(cub3d->scenedata->resolution.y
					/ (s.transformy))) * 0.8;
		s.drawstartx = -s.spritewidth / 2 + s.spritescreenx;
		if (s.drawstartx < 0)
			s.drawstartx = 0;
		s.drawendx = s.spritewidth / 2 + s.spritescreenx;
		if (s.drawendx >= cub3d->scenedata->resolution.x)
			s.drawendx = cub3d->scenedata->resolution.x - 1;
		draw_sprites_norm1(raycast, cub3d, &s);
		s.i++;
	}
}

typedef struct	s_raycast_mt
{
	t_cub3d		*cub3d;
	t_raycast	*raycast;
	int			phaser;
	int			limit;
	pthread_t	thread_id;
}				t_raycast_mt;

void		*raycaster_mt(void *arg)
{
	t_raycast_mt *r = (t_raycast_mt *)arg;

	while (r->phaser < r->limit)
	{
		r->raycast->hit = false;
		calc_pos_in_cameraplane(r->raycast, r->cub3d);
		calc_ray_position_and_direction(r->raycast, r->cub3d->player);
		calc_delta_intercept(r->raycast);
		calc_tilestep_and_intercept(r->raycast, r->cub3d);
		perform_dda(r->raycast, r->cub3d);
		calc_distance(r->raycast, r->cub3d);
		draw_line(r->raycast, r->cub3d);
		(r->phaser)++;
	}
	return (NULL);	
}

t_bool		raycaster(t_raycast *raycast, t_cub3d *cub3d)
{
	init_raycast(raycast, cub3d);
	if (cub3d->scenedata->textured_floor_and_ceiling)
		draw_textured_floor_and_ceiling(raycast, cub3d);
	else
		draw_colored_floors_and_ceiling(cub3d->mlx, cub3d->scenedata);
	

	t_raycast_mt r0;
	r0.cub3d = cub3d;
	r0.raycast = raycast;
	r0.phaser = 0;
	r0.limit = cub3d->mlx->resolution.x;

	t_raycast_mt r1;
	t_raycast_mt r2;
	t_raycast_mt r3;
	ft_memcpy(&r1, &r0, sizeof(t_raycast_mt));
	ft_memcpy(&r2, &r0, sizeof(t_raycast_mt));
	ft_memcpy(&r3, &r0, sizeof(t_raycast_mt));
	
	r1.limit = cub3d->mlx->resolution.x / 3;
	r2.phaser = r1.limit;
	r2.limit = 2 * (cub3d->mlx->resolution.x / 3);
	r3.phaser = r2.limit;

	pthread_create(&r0.thread_id, NULL, raycaster_mt, &r1);
	pthread_create(&r1.thread_id, NULL, raycaster_mt, &r2);
	pthread_create(&r2.thread_id, NULL, raycaster_mt, &r3);
	pthread_join(r1.thread_id, NULL);
	pthread_join(r2.thread_id, NULL);
	pthread_join(r3.thread_id, NULL);

	ft_printf("hallo?\n");

	raycast->sprite_update++;
	if (raycast->sprite_update % 10 == 0)
		sort_sprites(raycast, cub3d);
	draw_sprites(raycast, cub3d);
	return (noerr);
}
