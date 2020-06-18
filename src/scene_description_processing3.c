/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 21:32:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

static void	preprocess_mapline(char *line)
{
	const char	*line_org = line;
	size_t		spacecount;

	spacecount = 0;
	while (*line)
	{
		if (ft_isspace(*line) || *line == '\n')
		{
			*line = '0';
			spacecount++;
		}
		line++;
	}
	if (spacecount == ft_strlen(line_org))
		crit_error("Map:", "empty line in map!", NULL);
}

t_bool		scenedesc_process_map(t_scenedata *scenedata, char *line)
{
	if (!scenedata->map)
		scenedata->map = dynmem_init(MAP_APROX_LINE_COUNT);
	if (!scenedata->map)
	{
		crit_error("MALLOC", strerror(errno), NULL);
		return (err);
	}
	preprocess_mapline(line);
	return (dynmem_pushback(&scenedata->map,
			(unsigned char *)ft_strfdup(line, ' ')));
}

t_bool		scenedesc_process_textures_sprites(t_scenedata *scenedata,
		char *line)
{
	char	**elements;

	if (line[0] == 'S' && scenedata->f_textures[TEXT_SP])
		crit_error("Sprites:", "Double entry:", line);
	elements = ft_strsplit(line, ' ');
	if (elements && count_elements(elements) == 2)
	{
		if (ft_strncmp(elements[0], "S", 2) == 0)
			scenedata->f_textures[TEXT_SP] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "S", 1) == 0
				&& ft_isdigit(elements[0][1]))
		{
			scenedata->f_textures[TEXT_SPE + ft_atoi(elements[0] + 1)] =
				ft_strdup(elements[1]);
		}
		else
			crit_error("Sprites:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("Sprites:", "wrong number of elements (or malloc failure):",
			line);
	return (err);
}
