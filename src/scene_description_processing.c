/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/02 13:02:26 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void	destroy_elements(char **elements)
{
	int ctr;

	ctr = 0;
	while (elements[ctr] != NULL)
	{
		free(elements[ctr]);
		ctr++;
	}
	free(elements);
}

int		count_elements(char **elements)
{
	int ctr;

	ctr = 0;
	while (elements[ctr] != NULL)
		ctr++;
	return (ctr);
}

t_bool	scenedesc_process_resolution(t_scenedata *scenedata, char *line)
{
	char **elements;

	elements = ft_strsplit(line, ' ');
	if (elements)
	{
		if (ft_strncmp(elements[0], "R", 2) == 0)
		{
			scenedata->resolution.x = ft_atoi(elements[1]);
			scenedata->resolution.y = ft_atoi(elements[2]);
		}
		else
			crit_error("Scene description:", "bogus info on line:", line);
		if (elements[3] != NULL)
			crit_error("Scene description:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (err);
}

t_bool	scenedesc_process_textures(t_scenedata *scenedata, char *line)
{
	char	**elements;

	elements = ft_strsplit(line, ' ');
	if (elements && count_elements(elements) == 2)
	{
		if (ft_strncmp(elements[0], "NO", 3) == 0)
			scenedata->f_textures[TEXT_N] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "EA", 3) == 0)
			scenedata->f_textures[TEXT_E] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "SO", 3) == 0)
			scenedata->f_textures[TEXT_S] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "WE", 3) == 0)
			scenedata->f_textures[TEXT_W] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "S", 2) == 0)
			scenedata->f_textures[TEXT_SP] = ft_strdup(elements[1]);
		else
			crit_error("Scene description:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (err);
}

t_bool	scenedesc_process_colors(t_scenedata *scenedata, char *line)
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
				if (count_elements(colors) == 3)
				{
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

t_bool	scenedesc_process_map(t_scenedata *scenedata, char *line)
{
	if (!scenedata->map)
		scenedata->map = dynmem_init(MAP_APROX_LINE_COUNT);
	if (!scenedata->map)
	{
		crit_error("MALLOC", strerror(errno), NULL);
		return (err);
	}
	return (dynmem_pushback(&scenedata->map,
			(unsigned char *)ft_strfdup(line, ' ')));
}
