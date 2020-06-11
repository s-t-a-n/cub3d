/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/11 18:40:06 by sverschu      ########   odam.nl         */
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

static void		dump_scenedata_map_printl(char *line)
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

void			dump_scenedata_map(t_scenedata *scenedata)
{
	size_t	ctr;

	ft_printf("---------------------------------------\n");
	ctr = 0;
	while (ctr < scenedata->map->element_count)
	{
		dump_scenedata_map_printl((char *)scenedata->map->mem[ctr]);
		ctr++;
	}
	ft_printf("---------------------------------------\n");
}

void			dump_scenedata(t_scenedata *scenedata)
{
	int i;

	ft_printf("resolution:\t\t\t%i by %i\n", scenedata->resolution.x,
				scenedata->resolution.y);
	i = 0;
	while (i < TEXTURE_CAP)
	{
		ft_printf("texture[%i]: %s\n", i, scenedata->f_textures[i]);
		i++;
	}
	ft_printf("color ceiling:\t\t\t%i:%i:%i\n", scenedata->ceiling_color.r,
			scenedata->ceiling_color.g, scenedata->ceiling_color.b);
	ft_printf("color floor:\t\t\t%i:%i:%i\n", scenedata->floor_color.r,
			scenedata->floor_color.g, scenedata->floor_color.b);
	dump_scenedata_map(scenedata);
}

t_bool			lineismap(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		return (false);
	return (line[0] == '1' || line[0] == '0' || line[0] == '2');
}


t_bool			extract_scenedata_from_line(t_scenedata *scenedata, char *line)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (scenedesc_process_resolution(scenedata, line));
	else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "FL ", 3) == 0 || ft_strncmp(line, "CE ", 3) == 0)
		return (scenedesc_process_textures(scenedata, line));
	else if (ft_strncmp(line, "S ", 2) == 0
			|| (ft_strncmp(line, "S", 1) == 0 && ft_isdigit(*(line + 1))))
		return (scenedesc_process_textures_sprites(scenedata, line));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (scenedesc_process_colors(scenedata, line));
	else if (lineismap(line))
		return (scenedesc_process_map(scenedata, line));
	else
		crit_error("Scene description:", "bogus info on line:", line);
	return (err);
}

t_bool			build_scenedata(t_scenedata *scenedata, int fd)
{
	char		*line;
	int			error;

	error = noerr;
	init_scenedata(scenedata);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
			error = extract_scenedata_from_line(scenedata, line);
		free(line);
		if (error == err)
			break ;
	}
	free(line);
	postprocess_scenedata(scenedata);
	dump_scenedata(scenedata);
	return (verify_scenedata(scenedata));
}

t_bool			construct_scenedata(t_scenedata *scenedata, char *filename)
{
	int		fd;
	t_bool	error;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		crit_error("Scene description:", "file open error:", strerror(errno));
		return (err);
	}
	error = build_scenedata(scenedata, fd);
	if (close(fd) < 0)
		crit_error("Scene description:", "file close error:", strerror(errno));
	return (error);
}
