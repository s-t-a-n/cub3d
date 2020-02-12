/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 00:08:40 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 00:24:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	construct_player(t_scenedata *scenedata, t_player *player)
{
	player->pos.x = (float)scenedata->player_position.x;
	player->pos.y = (float)scenedata->player_position.y;
	convert_edirection_to_flvector2(scenedata->player_orientation,
			&player->viewdir);
	return (noerr);
}

t_bool	construct_game(t_scenedata *scenedata, t_player *player)
{
	construct_player(scenedata, player);
	return (noerr);
}
