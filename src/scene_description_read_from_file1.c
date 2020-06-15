/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 18:53:03 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

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

int				lineismap_orempty(char *line)
{
	while (*line && (ft_isspace(*line) || *line == '\n'))
		line++;
	if (*line == '\0')
		return (2);
	if (*line == '1' || *line == '0' || *line == '2')
		return (1);
	return (0);
}

t_bool			extract_scenedata_from_line(t_scenedata *scenedata, char *line)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (scenedesc_process_resolution(scenedata, line));
	else if (ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "FL ", 3) == 0
			|| ft_strncmp(line, "CE ", 3) == 0)
		return (scenedesc_process_textures(scenedata, line));
	else if (ft_strncmp(line, "S ", 2) == 0
			|| (ft_strncmp(line, "S", 1) == 0 && ft_isdigit(*(line + 1))))
		return (scenedesc_process_textures_sprites(scenedata, line));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (scenedesc_process_colors(scenedata, line));
	else if (lineismap_orempty(line) == 1)
	{
		scenedata->map_started = true;
		return (scenedesc_process_map(scenedata, line));
	}
	else if (lineismap_orempty(line) == 2 && !scenedata->map_started)
		return(noerr);
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
		error = extract_scenedata_from_line(scenedata, line);
		free(line);
		if (error == err)
			break ;
	}
	free(line);
	postprocess_scenedata(scenedata);
	return (verify_scenedata(scenedata));
}
