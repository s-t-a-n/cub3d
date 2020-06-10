/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster5.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:06:04 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:06:05 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dump_raycast(t_raycast *raycast)
{
	ft_printf("phaser:\t\t%i x %i\n", raycast->phaser.x, raycast->phaser.y);
	ft_printf("pos:\t\t%i x %i\n", raycast->pos.x, raycast->pos.y);
	ft_printf("tilestep:\t\t%i x %i\n", raycast->tilestep.x,
			raycast->tilestep.y);
	ft_printf("phaser:\t\t%i x %i\n", raycast->phaser.x,
			raycast->phaser.y);
	ft_printf("dir:\t\t%f x %f\n", raycast->dir.x, raycast->dir.y);
	ft_printf("camplane:\t\t%f x %f\n", raycast->camplane.x,
			raycast->camplane.y);
	ft_printf("campos:\t\t%f x %f\n", raycast->campos.x,
			raycast->campos.y);
	ft_printf("intercept:\t\t%f x %f\n", raycast->intercept.x,
			raycast->intercept.y);
	ft_printf("delta_intercept:\t\t%f x %f\n", raycast->delta_intercept.x,
			raycast->delta_intercept.y);
	ft_printf("hit:\t\t%i\n", raycast->hit);
	ft_printf("side:\t\t%i\n", raycast->side);
	ft_printf("item:\t\t%i\n", raycast->item);
	ft_printf("distance:\t\t%f\n", raycast->distance);
}

void	calc_pos_in_cameraplane(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->campos.y = 0.0;
	raycast->campos.x = 2.0 * raycast->phaser.x / cub3d->mlx->resolution.x - 1;
}

void	calc_ray_position_and_direction(t_raycast *raycast, t_player *player)
{
	raycast->pos.x = (int)player->pos.x;
	raycast->pos.y = (int)player->pos.y;
	raycast->dir.x = player->vdir.x + raycast->camplane.x * raycast->campos.x;
	raycast->dir.y = player->vdir.y + raycast->camplane.y * raycast->campos.x;
}

void	calc_tilestep_and_intercept(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->dir.x < 0)
	{
		raycast->tilestep.x = -1;
		raycast->intercept.x = (cub3d->player->pos.x - raycast->pos.x)
			* raycast->delta_intercept.x;
	}
	else
	{
		raycast->tilestep.x = 1;
		raycast->intercept.x = (raycast->pos.x + 1.0 - cub3d->player->pos.x)
			* raycast->delta_intercept.x;
	}
	if (raycast->dir.y < 0)
	{
		raycast->tilestep.y = -1;
		raycast->intercept.y = (cub3d->player->pos.y - raycast->pos.y)
			* raycast->delta_intercept.y;
	}
	else
	{
		raycast->tilestep.y = 1;
		raycast->intercept.y = (raycast->pos.y + 1.0 - cub3d->player->pos.y)
			* raycast->delta_intercept.y;
	}
}

void	calc_delta_intercept(t_raycast *raycast)
{
	raycast->delta_intercept.x = fabs(1.0 / raycast->dir.x);
	raycast->delta_intercept.y = fabs(1.0 / raycast->dir.y);
}
