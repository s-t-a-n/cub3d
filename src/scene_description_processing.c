/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 00:03:04 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void	destroy_elements(char **elements)
{
	int ctr;

	ctr = 0;
	while(elements[ctr] != NULL)
	{
		free (elements[ctr]);
		ctr++;
	}
	free (elements);
}

int	count_elements(char **elements)
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
			pscene_error("bogus line!");
		if (elements[3] != NULL)
			pscene_error("resolution has bogus data at the end!");
		destroy_elements(elements);
		return(noerr);
	}
	else
		perror("resolution processing");
	return (err);
}

t_bool	scenedesc_process_textures(t_scenedata *scenedata, char *line)
{
	char	**elements;

	elements = ft_strsplit(line, ' ');
	if (elements && count_elements(elements) == 2)
	{
		if (ft_strncmp(elements[0], "NO", 3) == 0)
			scenedata->f_texture_north = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "EA", 3) == 0)
			scenedata->f_texture_east = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "SO", 3) == 0)
			scenedata->f_texture_south = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "WE", 3) == 0)
			scenedata->f_texture_west = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "S", 2) == 0)
			scenedata->f_sprite_texture = ft_strdup(elements[1]);
		destroy_elements(elements);
		return (noerr);
	}
	else
		perror("resolution processing");
	return (err);
}

t_bool	scenedesc_process_colors(t_scenedata *scenedata, char *line)
{
	char **elements;
	char **colors;

	elements = ft_strsplit(line, ' ');
	if (elements)
	{
		if (ft_strncmp(elements[0], "C ", 2) == 0 || ft_strncmp(elements[0], "F ", 2))
		{
			colors = ft_strsplit(elements[1], ',');
			if (colors)
			{
				if (count_elements(colors) == 3)
				{
					if (ft_strncmp(elements[0], "C", 2) == 0)
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
					destroy_elements(elements);
					return (noerr);
				}
				else
					pscene_error("colors processing: bogus color count");
				destroy_elements(colors);
			}
			else
				perror("colors processing");
		}
		else
			pscene_error("colors processing: bogus input data!");
		destroy_elements(elements);
	}
	else
		perror("colors processing");
	return (err);
}

t_bool	scenedesc_process_map(t_scenedata *scenedata, char *line)
{
	if (!scenedata->map)
		scenedata->map = dynmem_init(MAP_APROX_LINE_COUNT);
	if (!scenedata->map)
	{
		perror("map processing");
		return (err);
	}
	return(dynmem_pushback(&scenedata->map, (unsigned char *)ft_strfdup(line, ' ')));
}
