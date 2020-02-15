/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 00:08:40 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 18:50:55 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	construct_player(t_cub3d *cub3d)
{
	cub3d->player->pos.x = cub3d->scenedata->player_position.x;
	cub3d->player->pos.y = cub3d->scenedata->player_position.y;
	//convert_edirection_to_flvector2(cub3d->scenedata->player_orientation, &cub3d->player->viewdir);
	return (noerr);
}

t_bool	construct_game(t_cub3d *cub3d, t_scenedata *scenedata)
{
	cub3d->scenedata = scenedata;
	construct_player(cub3d);
	return (noerr);
}
