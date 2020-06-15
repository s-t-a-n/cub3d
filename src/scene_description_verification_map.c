/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification_map.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 22:02:25 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 18:53:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** dont blame me; blame Norminette; this would be a perfectly valid case
** for a 25lines+ function
*/

static t_bool		smafpp_sub(t_scenedata *scenedata, size_t xctr, size_t yctr,
				char ch)
{
	if (ch == 'N' || ch == 'E'
			|| ch == 'S' || ch == 'W')
	{
		if (scenedata->player_position.x != -1)
			crit_error("Scene description, map:",
					"multiple player positions!", NULL);
		scenedata->player_position.x = xctr;
		scenedata->player_position.y = yctr;
		if (ch == 'N')
			scenedata->player_orientation = north;
		if (ch == 'E')
			scenedata->player_orientation = east;
		if (ch == 'S')
			scenedata->player_orientation = south;
		if (ch == 'W')
			scenedata->player_orientation = west;
		scenedata->map->mem[yctr][xctr] = '0';
		return (true);
	}
	return (false);
}

/*
** run through the map and look for illegal nodes and check if there is a
** playerposition set (and that there is no duplicate)
*/

t_bool				scan_map_and_find_player_position(t_scenedata *scenedata)
{
	size_t			yctr;
	size_t			xctr;
	unsigned char	*xhead;

	yctr = 0;
	scenedata->player_position.x = -1;
	while (yctr < scenedata->map->element_count)
	{
		xhead = scenedata->map->mem[yctr];
		xctr = 0;
		while (xhead[xctr])
		{
			if (!(smafpp_sub(scenedata, xctr, yctr, xhead[xctr])
						|| xhead[xctr] == '0' || xhead[xctr] == '1'
						|| xhead[xctr] == '2'))
				crit_error("Scene description, map:", "bogus map entry:",
						(char *)&xhead[xctr]);
			xctr++;
		}
		yctr++;
	}
	if (scenedata->player_position.x == -1)
		crit_error("Scene description, map", "no player position found!", NULL);
	return (noerr);
}

static t_vector2	adjust_position(t_direction dir, t_vector2 pos)
{
	if (dir == north)
		pos.y -= 1;
	else if (dir == east)
		pos.x += 1;
	else if (dir == south)
		pos.y += 1;
	else if (dir == west)
		pos.x -= 1;
	else if (dir == northeast)
	{
		pos.y -= 1;
		pos.x += 1;
	}
	else if (dir == northwest)
	{
		pos.y -= 1;
		pos.x -= 1;
	}
	else if (dir == southeast)
	{
		pos.y += 1;
		pos.x += 1;
	}
	else if (dir == southwest)
	{
		pos.y += 1;
		pos.x -= 1;
	}
	return (pos);
}

static t_bool		breachfinder(char **map, int ymax,
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
				&& pos.y != ymax-1
				&& pos.x != 0
				&& pos.x != (int)ft_strlen(map[pos.y])-1
				&& map[pos.y][pos.x] == '2')
			return (false);
	}
	return (breachfinder(map, ymax, pos, north)
	|| breachfinder(map, ymax, pos, northeast)
	|| breachfinder(map, ymax, pos, east)
	|| breachfinder(map, ymax, pos, southeast)
	|| breachfinder(map, ymax, pos, south)
	|| breachfinder(map, ymax, pos, southwest)
	|| breachfinder(map, ymax, pos, west)
	|| breachfinder(map, ymax, pos, northwest));
}

/*
** start from player position and recursively check all neighbouring nodes for
** a breach in the outer wall
*/

t_bool				check_if_player_is_enclosed(t_scenedata *scenedata)
{
	t_vector2 pos;

	pos = scenedata->player_position;
	if (breachfinder((char **)scenedata->map->mem,
				scenedata->map->element_count, pos, nodir))
	{
		dump_scenedata_map(scenedata);
		crit_error("Scene validation, map:", "breach in wall found!", NULL);
	}
	return (true);
}
