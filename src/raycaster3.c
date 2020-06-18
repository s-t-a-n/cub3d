/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster3.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 18:58:45 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 18:59:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void		draw_textured_floor_and_ceiling_norm1(t_raycast *raycast,
					t_cub3d *cub3d, t_draw_tex_floor_ceiling *q)
{
	while (q->ctr.x < cub3d->mlx->resolution.x)
	{
		q->text_pos.x = (int)fabs(q->floor_texture->size.x
				* (q->floor.x - (int)q->floor.x));
		q->text_pos.y = (int)fabs(q->floor_texture->size.y
				* (q->floor.y - (int)q->floor.y));
		q->floor.x += q->floor_step.x;
		q->floor.y += q->floor_step.y;
		mlx_wpixel(cub3d->mlx->image_nact, q->ctr, mlx_rpixel(q->text_pos,
					q->floor_texture));
		q->text_pos.x = (int)fabs(q->ceiling_texture->size.x
				* (q->floor.x - (int)q->floor.x));
		q->text_pos.y = (int)fabs(q->ceiling_texture->size.y
				* (q->floor.y - (int)q->floor.y));
		q->nctr.x = q->ctr.x;
		q->nctr.y = cub3d->mlx->resolution.y - q->ctr.y - 1;
		mlx_wpixel(cub3d->mlx->image_nact, q->nctr, mlx_rpixel(q->text_pos,
					q->ceiling_texture));
		q->ctr.x++;
	}
	(void)raycast;
}

void			draw_textured_floor_and_ceiling(t_raycast *raycast,
					t_cub3d *cub3d)
{
	t_draw_tex_floor_ceiling q;

	q.floor_texture = &cub3d->mlx->textures[TEXT_FL];
	q.ceiling_texture = &cub3d->mlx->textures[TEXT_CE];
	q.ray_dir_left.x = cub3d->player->vdir.x - raycast->camplane.x;
	q.ray_dir_left.y = cub3d->player->vdir.y - raycast->camplane.y;
	q.ray_dir_right.x = cub3d->player->vdir.x + raycast->camplane.x;
	q.ray_dir_right.y = cub3d->player->vdir.y + raycast->camplane.y;
	q.camera_y = cub3d->mlx->resolution.y / 2;
	q.ctr.y = cub3d->mlx->resolution.y / 2;
	while (q.ctr.y < cub3d->mlx->resolution.y)
	{
		q.cur_y = q.ctr.y - cub3d->mlx->resolution.y / 2;
		q.camera_y_rel = q.cur_y == 0.0 ? 0.0 : q.camera_y / q.cur_y;
		q.floor_step.x = q.camera_y_rel * (q.ray_dir_right.x - q.ray_dir_left.x)
			/ cub3d->mlx->resolution.x;
		q.floor_step.y = q.camera_y_rel * (q.ray_dir_right.y - q.ray_dir_left.y)
			/ cub3d->mlx->resolution.x;
		q.floor.x = cub3d->player->pos.x + q.camera_y_rel * q.ray_dir_left.x;
		q.floor.y = cub3d->player->pos.y + q.camera_y_rel * q.ray_dir_left.y;
		q.ctr.x = 0;
		draw_textured_floor_and_ceiling_norm1(raycast, cub3d, &q);
		q.ctr.y++;
	}
}

inline void		draw_textured_line_norm0(t_draw_tex_line *s, t_cub3d *cub3d,
					t_vector2 pos, double lh)
{
	while (s->yctr < pos.y + ((lh > cub3d->mlx->resolution.y)
				? cub3d->mlx->resolution.y : (int)lh))
	{
		s->tp.y = (int)s->tj;
		s->tj += s->tj_step;
		s->ip.x = pos.x;
		s->ip.y = s->yctr;
		mlx_wpixel(cub3d->mlx->image_nact, s->ip, mlx_rpixel(s->tp, s->te));
		s->yctr++;
	}
}

void			draw_textured_line(t_raycast *raycast, t_cub3d *cub3d,
					t_vector2 pos, double lh)
{
	t_draw_tex_line		s;

	s.te = select_texture(cub3d, raycast, raycast->item);
	if (raycast->side == 0)
		s.wp.x = cub3d->player->pos.y + raycast->distance * raycast->dir.y;
	else
		s.wp.x = cub3d->player->pos.x + raycast->distance * raycast->dir.x;
	s.wp.x -= floor(s.wp.x);
	s.tp.x = (int)(s.wp.x * (double)s.te->size.x);
	if (raycast->side == 0 && raycast->dir.x > 0)
		s.tp.x = s.te->size.x - s.tp.x - 1;
	if (raycast->side == 1 && raycast->dir.y < 0)
		s.tp.x = s.te->size.x - s.tp.x - 1;
	s.tj_step = (double)s.te->size.y / (double)lh;
	s.tj = fabs(pos.y - cub3d->mlx->resolution.y / 2 + lh / 2) * s.tj_step;
	s.yctr = pos.y;
	draw_textured_line_norm0(&s, cub3d, pos, lh);
}

void			draw_colored_line(t_raycast *raycast, t_cub3d *cub3d,
					t_vector2 pos, double lineheight)
{
	t_vector2 size;

	if (lineheight > cub3d->mlx->resolution.y)
		lineheight = cub3d->mlx->resolution.y;
	size.y = lineheight;
	size.x = 1;
	if (raycast->side)
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00C74D0F);
	else
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00A9410D);
}
