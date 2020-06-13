/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:18:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

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
