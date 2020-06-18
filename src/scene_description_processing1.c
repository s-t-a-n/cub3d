/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 21:31:14 by sverschu      ########   odam.nl         */
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
										char **elements,
										char **colors)
{
	if (count_elements(colors) == 3)
	{
		verify_color_bogus(colors);
		if (elements[0][0] == 'C')
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

t_bool		scenedesc_process_colors_norm1(t_scenedata *scenedata,
										char *line,
										char ***elements)
{
	if (line[0] == 'C' && scenedata->ceiling_color.r != -1)
		crit_error("Scene description:", "Double entry:", line);
	if (line[0] == 'F' && scenedata->floor_color.r != -1)
		crit_error("Scene description:", "Double entry:", line);
	*elements = ft_strsplit(line, ' ');
	return (true);
}

t_bool		scenedesc_process_colors(t_scenedata *scenedata, char *line)
{
	char **elements;
	char **colors;

	if (scenedesc_process_colors_norm1(scenedata, line, &elements) && elements)
	{
		if ((elements[0][0] == 'C' || elements[0][0] == 'F')
				&& elements[1] && !elements[2])
		{
			colors = elements[1] ? ft_strsplit(elements[1], ',') : NULL;
			if (colors)
			{
				if (scenedesc_process_colors_norm0(scenedata, line, elements,
							colors))
					return (noerr);
			}
			else
				crit_error("Colors:", "cant split elements:", strerror(errno));
		}
		else
			crit_error("Scene description:", "bogus info on line:", line);
		free(elements);
	}
	else
		crit_error("Colors:", "bogus info: (or malloc failure)", line);
	return (err);
}
