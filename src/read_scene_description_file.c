/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_description_file.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:21:07 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/06 20:56:05 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

int			extract_scenedata_from_line(char *line)
{
	if (line[0] == 'a')
		printf("found a!\n");
	return (0);

}

void		pscene_error(int error)
{
	printf("error : %i\n", error);
}

t_scenedata *build_scenedata(int fd)
{
	char		*line;
	t_scenedata	*scenedata;
	int			error;

	scenedata = malloc(sizeof(t_scenedata));
	if (scenedata)
	{
		while (get_next_line(fd, &line) > 0)
		{
			error = extract_scenedata_from_line(line);
			free(line);
			if (error)
			{
				pscene_error(error);
				break;
			}
		}
	}
	else
		perror("scenedata file");
	return (scenedata);
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
	if (close(fd) < 0)
		perror("scenedata file");
	return(scenedata);
}
