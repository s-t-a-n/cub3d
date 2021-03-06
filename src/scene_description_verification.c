/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 18:36:50 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:08:32 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static t_bool	file_exists(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		crit_error("Scene description:", filename, strerror(errno));
		return (err);
	}
	else
	{
		if (close(fd) < 0)
		{
			crit_error("Scene description:", filename, strerror(errno));
			return (err);
		}
		return (noerr);
	}
}

t_bool			scenedesc_verify_textures(t_scenedata *scenedata)
{
	int i;

	i = 0;
	while (i < TEXTURE_STOCK + (scenedata->textured_floor_and_ceiling ? 2 : 0)
			+ scenedata->extra_sprites)
	{
		if (!file_exists(scenedata->f_textures[i]))
			return (err);
		i++;
	}
	return (noerr);
}

static t_bool	check_colorcode(int colorcode)
{
	t_bool error;

	error = (colorcode >= 0 && colorcode <= 255);
	if (error == err)
		crit_error("Color:", "colorcode invalid:",
				ft_itoa(colorcode));
	return (error);
}

t_bool			scenedesc_verify_colors(t_scenedata *scenedata)
{
	t_bool errors;

	errors = (check_colorcode(scenedata->floor_color.r)
				&& check_colorcode(scenedata->floor_color.g)
				&& check_colorcode(scenedata->floor_color.b)
				&& check_colorcode(scenedata->ceiling_color.r)
				&& check_colorcode(scenedata->ceiling_color.b)
				&& check_colorcode(scenedata->ceiling_color.r));
	if (errors == noerr)
	{
		scenedata->floor_trgb = trgb(0, scenedata->floor_color.r,
				scenedata->floor_color.g, scenedata->floor_color.b);
		scenedata->ceiling_trgb = trgb(0, scenedata->ceiling_color.r,
				scenedata->ceiling_color.g, scenedata->ceiling_color.b);
		return (noerr);
	}
	return (err);
}

t_bool			scenedesc_verify_map(t_scenedata *scenedata)
{
	scan_map_and_find_player_position(scenedata);
	check_if_player_is_enclosed(scenedata);
	return (scenedata != NULL);
}
