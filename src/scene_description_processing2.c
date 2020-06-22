/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing1.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 16:57:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/22 19:08:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

t_bool	scenedesc_process_resolution(t_scenedata *scenedata, char *line)
{
	char **elements;

	elements = ft_strsplit(line, ' ');
	if (elements)
	{
		if (ft_strncmp(elements[0], "R", 2) == 0
				&& element_only_has_numbers(elements))
		{
			scenedata->resolution.x = ft_atoi(elements[1]);
			scenedata->resolution.y = ft_atoi(elements[2]);
		}
		else
			crit_error("Resolution:", "bogus info on line:", line);
		if (elements[3] != NULL)
			crit_error("Resolution:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("Resolution:", "couldnt split elements: ", strerror(errno));
	return (err);
}

void	scenedesc_process_textures_norm0(t_scenedata *scenedata, char *line,
		char ***elements)
{
	if ((ft_strncmp(line, "NO", 2) == 0 && scenedata->f_textures[TEXT_N])
	|| (ft_strncmp(line, "EA", 2) == 0 && scenedata->f_textures[TEXT_E])
	|| (ft_strncmp(line, "SO", 2) == 0 && scenedata->f_textures[TEXT_S])
	|| (ft_strncmp(line, "WE", 2) == 0 && scenedata->f_textures[TEXT_W])
	|| (ft_strncmp(line, "FL", 2) == 0 && scenedata->f_textures[TEXT_FL])
	|| (ft_strncmp(line, "CE", 2) == 0 && scenedata->f_textures[TEXT_CE]))
		crit_error("Textures:", "Double entry:", line);
	*elements = ft_strsplit(line, ' ');
}

t_bool	scenedesc_process_textures(t_scenedata *scenedata, char *line)
{
	char	**elements;

	scenedesc_process_textures_norm0(scenedata, line, &elements);
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
		else if (ft_strncmp(elements[0], "FL", 2) == 0)
			scenedata->f_textures[TEXT_FL] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "CE", 2) == 0)
			scenedata->f_textures[TEXT_CE] = ft_strdup(elements[1]);
		else
			crit_error("Textures:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("Textures:", "bogus info on line:", line);
	return (err);
}
