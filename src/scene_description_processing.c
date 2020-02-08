/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 20:41:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/08 22:16:20 by sverschu      ########   odam.nl         */
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
		perror("resolution processing:");
	return (err);
}

t_bool	scenedesc_process_textures(t_scenedata *scenedata, char *line)
{
	char	**elements;

	printf("processing for |%s|\n", line);
	elements = ft_strsplit(line, ' ');
	if (elements)
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
	return (err);
}

t_bool	scenedesc_process_colors(t_scenedata *scenedata, char *line)
{
	scenedata = NULL;
	line = NULL;
	return (err);
}

t_bool	scenedesc_process_map(t_scenedata *scenedata, char *line)
{
	scenedata = NULL;
	line = NULL;
	return (err);
}
