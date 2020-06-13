/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:18:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void		init_scenedata(t_scenedata *scenedata)
{
	int i;

	i = 0;
	while (i < TEXTURE_CAP)
	{
		scenedata->f_textures[i] = NULL;
		i++;
	}
	scenedata->textured_floor_and_ceiling = false;
	scenedata->resolution.x = -1;
	scenedata->resolution.y = -1;
	scenedata->floor_color.r = -1;
	scenedata->floor_color.g = -1;
	scenedata->floor_color.b = -1;
	scenedata->ceiling_color.b = -1;
	scenedata->ceiling_color.b = -1;
	scenedata->ceiling_color.b = -1;
	scenedata->map = NULL;
	scenedata->error = 0;
}

void		postprocess_scenedata(t_scenedata *scenedata)
{
	int i;

	if (scenedata->f_textures[TEXT_FL] || scenedata->f_textures[TEXT_CE])
		scenedata->textured_floor_and_ceiling = true;
	scenedata->extra_sprites = 0;
	i = TEXT_SPE;
	while (scenedata->f_textures[i])
	{
		scenedata->extra_sprites++;
		i++;
	}
}

void		destroy_scenedata(t_scenedata *scenedata)
{
	int i;

	i = 0;
	while (i < TEXTURE_CAP)
	{
		free(scenedata->f_textures[i]);
		i++;
	}
	dynmem_destroy(scenedata->map);
}

t_bool		verify_scenedata(t_scenedata *scenedata)
{
	if (!scenedesc_verify_resolution(scenedata)
			|| !scenedesc_verify_textures(scenedata)
			|| !scenedesc_verify_colors(scenedata)
			|| !scenedesc_verify_map(scenedata))
	{
		destroy_scenedata(scenedata);
		return (err);
	}
	return (noerr);
}

void		dump_scenedata_map_printl(char *line)
{
	while (*line)
	{
		if (*line == MAP_WALKABLE)
			ft_printf(" \e[101m%c\e[49m", *line);
		else if (*line == '0')
			ft_printf(" \e[41m%c\e[49m", *line);
		else if (*line == '1')
			ft_printf(" \e[44m%c\e[49m", *line);
		else if (*line == '2')
			ft_printf(" \e[104m%c\e[49m", *line);
		else
			ft_printf(" \e[103m%c\e[49m", *line);
		if (*line == MAP_RAYHIT)
			*line = MAP_WALL;
		line++;
	}
	ft_printf("\n");
}
