/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification_map1.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 16:32:21 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/15 16:32:39 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool		breachfinder(char **map, int ymax,
		t_vector2 pos, t_direction dir)
{
	if (dir != nodir)
	{
		pos = adjust_position(dir, pos);
		if (pos.y < 0
				|| pos.y >= ymax
				|| pos.x < 0
				|| pos.x >= (int)ft_strlen(map[pos.y]))
			return (true);
		else if (map[pos.y][pos.x] == '1'
				|| map[pos.y][pos.x] == MAP_WALKABLE)
			return (false);
		else if (map[pos.y][pos.x] == '0')
			map[pos.y][pos.x] = MAP_WALKABLE;
		else if (pos.y != 0
				&& pos.y != ymax - 1
				&& pos.x != 0
				&& pos.x != (int)ft_strlen(map[pos.y]) - 1
				&& map[pos.y][pos.x] == '2')
			return (false);
	}
	return (breachfinder_norm0(map, ymax, pos));
}

t_bool		breachfinder_norm0(char **map, int ymax,
		t_vector2 pos)
{
	return (breachfinder(map, ymax, pos, north)
	|| breachfinder(map, ymax, pos, northeast)
	|| breachfinder(map, ymax, pos, east)
	|| breachfinder(map, ymax, pos, southeast)
	|| breachfinder(map, ymax, pos, south)
	|| breachfinder(map, ymax, pos, southwest)
	|| breachfinder(map, ymax, pos, west)
	|| breachfinder(map, ymax, pos, northwest));
}
