/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_description_file.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:21:07 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/08 22:05:46 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void		pscene_error(char *errordesc)
{
	ft_putstr_fd("scenedesc: ", 2);
	ft_putendl_fd(errordesc, 2);
}

t_scenedata	*init_scenedata()
{
	t_scenedata *scenedata;

	scenedata = malloc(sizeof(t_scenedata));
	if (scenedata)
	{
		scenedata->resolution.x = -1;
		scenedata->resolution.y = -1;
		scenedata->f_texture_north = NULL;
		scenedata->f_texture_east = NULL;
		scenedata->f_texture_south = NULL;
		scenedata->f_texture_west = NULL;
		scenedata->f_sprite_texture = NULL;
		scenedata->floor_color.r = -1;
		scenedata->floor_color.g = -1;
		scenedata->floor_color.b = -1;
		scenedata->ceiling_color.b = -1;
		scenedata->ceiling_color.b = -1;
		scenedata->ceiling_color.b = -1;
		scenedata->map = NULL;
		scenedata->error = 0;
	}
	return (scenedata);
}

void		destroy_scenedata(t_scenedata *scenedata)
{
	if (scenedata)
	{
		free(scenedata->f_texture_north);
		free(scenedata->f_texture_east);
		free(scenedata->f_texture_south);
		free(scenedata->f_texture_west);
		free(scenedata->f_sprite_texture);
		free(scenedata->map);
	}
	free(scenedata);
}

t_scenedata	*verify_scenedata(t_scenedata *scenedata)
{
	if (!scenedesc_verify_resolution(scenedata)
			|| !scenedesc_verify_textures(scenedata)
			|| !scenedesc_verify_colors(scenedata)
			|| !scenedesc_verify_map(scenedata))
	{
		destroy_scenedata(scenedata);
		return (NULL);
	}
	return (scenedata);
}

t_bool			extract_scenedata_from_line(t_scenedata *scenedata, char *line)
{
	if (line[0] == 'R')
		return(scenedesc_process_resolution(scenedata, line));
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		return(scenedesc_process_textures(scenedata, line));
	return (err);
}

t_scenedata *build_scenedata(int fd)
{
	char		*line;
	t_scenedata	*scenedata;
	int			error;

	scenedata = init_scenedata();
	if (scenedata)
	{
		while (get_next_line(fd, &line) > 0)
		{
			error = extract_scenedata_from_line(scenedata, line);
			free(line);
			if (error == err)
				break;
		}
	}
	else
		perror("scenedata file");
	return (verify_scenedata(scenedata));
}

t_scenedata	*get_scenedata(char *filename)
{
	int fd;
	t_scenedata *scenedata;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("scenedata file");
		return (NULL);
	}
	scenedata = build_scenedata(fd);
	if (!scenedata)
		pscene_error("file appears to be malformed!");
	if (close(fd) < 0)
		perror("scenedata file");
	return(scenedata);
}
