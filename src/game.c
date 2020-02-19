/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 00:08:40 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/18 13:36:22 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	construct_player(t_cub3d *cub3d)
{
	cub3d->player->pos.x = cub3d->scenedata->player_position.x;
	cub3d->player->pos.y = cub3d->scenedata->player_position.y;
	cub3d->player->mov_speed = PLAYER_DEF_MOVE_SPEED;
	cub3d->player->rot_speed = PLAYER_DEF_ROT_SPEED;
	//convert_edirection_to_flvector2(cub3d->scenedata->player_orientation, &cub3d->player->viewdir);
	return (noerr);
}

t_bool	construct_game(t_cub3d *cub3d)
{
	construct_player(cub3d);
	return (noerr);
}

int	game_update(t_cub3d *cub3d)
{
	int render;

	render = false;
	if (cub3d->mlx->keystate != KB_DEFAULT)
		render += keyhandler(cub3d->mlx->keystate, cub3d);
	if (render == true)
		render_frame(cub3d);
	return (noerr);
}
