/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 18:36:50 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/09 23:40:21 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

t_bool			scenedesc_verify_resolution(t_scenedata *scenedata)
{
	t_bool error;
	
	error = (!(scenedata->resolution.x <= 0
			|| scenedata->resolution.x > 5120
			|| scenedata->resolution.y <= 0
			|| scenedata->resolution.y > 2880));
	if (error == err)
		pscene_error("resolution was not set or is malformed!");
	return (error);
}

static t_bool	file_exists(char *filename)
{
	int fd;

	//ft_printf("test file : %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		perror(filename);
		return (err);
	}
	else
	{
		if (close(fd) < 0)
		{
			perror(filename);
			return (err);
		}
		return (noerr);
	}
}

t_bool			scenedesc_verify_textures(t_scenedata *scenedata)
{
	return (file_exists(scenedata->f_texture_north)
			&& file_exists(scenedata->f_texture_east)
			&& file_exists(scenedata->f_texture_south)
			&& file_exists(scenedata->f_texture_west)
			&& file_exists(scenedata->f_sprite_texture));
}

t_bool			scenedesc_verify_colors(t_scenedata *scenedata)
{
	return (noerr);
	return (scenedata == NULL);
}

t_bool			scenedesc_verify_map(t_scenedata *scenedata)
{
	return (noerr);
	return (scenedata != NULL);
}
