/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_description_file.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:21:07 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 00:02:33 by sverschu      ########   odam.nl         */
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
		dynmem_destroy(scenedata->map);
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
		ft_printf("verification failed!\n");
		destroy_scenedata(scenedata);
		return (NULL);
	}
	return (scenedata);
}

void			dump_scenedata_map(t_scenedata *scenedata)
{
	size_t	ctr;
	
	ctr = 0;
	while (ctr < scenedata->map->element_count)
	{
		ft_printf("map:\t\t\t\t%s\n", scenedata->map->mem[ctr]);
		ctr++;
	}
}

void			dump_scenedata(t_scenedata *scenedata)
{
	ft_printf("resolution:\t\t\t%i by %i\n",scenedata->resolution.x, scenedata->resolution.y);
	ft_printf("texture north:\t\t\t%s\n",scenedata->f_texture_north);
	ft_printf("texture east:\t\t\t%s\n",scenedata->f_texture_east);
	ft_printf("texture south:\t\t\t%s\n",scenedata->f_texture_south);
	ft_printf("texture west:\t\t\t%s\n",scenedata->f_texture_west);
	ft_printf("texture sprite:\t\t\t%s\n",scenedata->f_sprite_texture);
	ft_printf("color ceiling:\t\t\t%i:%i:%i\n",scenedata->ceiling_color.r,scenedata->ceiling_color.g,scenedata->ceiling_color.b);
	ft_printf("color floor:\t\t\t%i:%i:%i\n",scenedata->floor_color.r,scenedata->floor_color.g,scenedata->floor_color.b);
	dump_scenedata_map(scenedata);
}

t_bool			extract_scenedata_from_line(t_scenedata *scenedata, char *line)
{
	if (line[0] == '1' || line[0] == '0')
		return(scenedesc_process_map(scenedata, line));
	else if (line[0] == 'R')
		return(scenedesc_process_resolution(scenedata, line));
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		return(scenedesc_process_textures(scenedata, line));
	else if (line[0] == 'F' || line[0] == 'C')
		return(scenedesc_process_colors(scenedata, line));
	else
		pscene_error("bogus information in scenedescription file!");
	return (err);
}

t_scenedata *build_scenedata(int fd)
{
	char		*line;
	t_scenedata	*scenedata;
	int			error;

	error = noerr;
	scenedata = init_scenedata();
	if (scenedata)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (line[0])
				error = extract_scenedata_from_line(scenedata, line);
			free(line);
			if (error == err)
				break;
		}
		free(line);
	}
	else
		perror("scenedata file");
	dump_scenedata(scenedata);
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
