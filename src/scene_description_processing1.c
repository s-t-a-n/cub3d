/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing1.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 16:57:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:00:17 by sverschu      ########   odam.nl         */
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
		else if (ft_strncmp(elements[0], "FL", 2) == 0)
			scenedata->f_textures[TEXT_FL] = ft_strdup(elements[1]);
		else if (ft_strncmp(elements[0], "CE", 2) == 0)
			scenedata->f_textures[TEXT_CE] = ft_strdup(elements[1]);
		else
			crit_error("Scene description:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (err);
}

t_bool	scenedesc_process_textures_sprites(t_scenedata *scenedata, char *line)
{
	char	**elements;

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
			crit_error("Scene description:", "bogus info on line:", line);
		destroy_elements(elements);
		return (noerr);
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (err);
}
