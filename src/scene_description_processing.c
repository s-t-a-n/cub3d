/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/15 16:31:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

static void	verify_color_bogus(char **colors)
{
	int i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				crit_error("Scene description:", "bogus info in colors", NULL);
			j++;
		}
		i++;
	}
}

t_bool		scenedesc_process_colors_norm0(t_scenedata *scenedata,
										char *line,
										char *elements,
										char **colors)
{
	if (count_elements(colors) == 3)
	{
		verify_color_bogus(colors);
		if (elements[0] == 'C')
		{
			scenedata->ceiling_color.r = ft_atoi(colors[0]);
			scenedata->ceiling_color.g = ft_atoi(colors[1]);
			scenedata->ceiling_color.b = ft_atoi(colors[2]);
		}
		else
		{
			scenedata->floor_color.r = ft_atoi(colors[0]);
			scenedata->floor_color.g = ft_atoi(colors[1]);
			scenedata->floor_color.b = ft_atoi(colors[2]);
		}
		destroy_elements(colors);
		free(elements);
		return (noerr);
	}
	else
		crit_error("Scene description:", "bogus info on line:", line);
	destroy_elements(colors);
	return (err);
}

t_bool		scenedesc_process_colors(t_scenedata *scenedata, char *line)
{
	char *elements;
	char **colors;

	elements = ft_strfdup(line, ' ');
	if (elements)
	{
		if (elements[0] == 'C' || elements[0] == 'F')
		{
			colors = ft_strsplit(elements + 1, ',');
			if (colors)
			{
				if (scenedesc_process_colors_norm0(scenedata, line, elements,
							colors))
					return (noerr);
			}
			else
				crit_error("MALLOC", strerror(errno), NULL);
		}
		else
			crit_error("Scene description:", "bogus info on line:", line);
		free(elements);
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (err);
}

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
		crit_error("Scene description:", "empty line in map!", NULL);
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
