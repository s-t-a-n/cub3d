/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:51:27 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

static t_bool	extension_isvalid(char *filename)
{
	const size_t len = ft_strlen(filename);
	const size_t ext_len = ft_strlen(EXTENSION);

	if (ext_len >= len)
		return (false);
	else
		return (ft_strncmp(&filename[len - ext_len], EXTENSION, ext_len) == 0);
}

t_bool			construct_scenedata(t_scenedata *scenedata, char *filename)
{
	int		fd;
	t_bool	error;

	if (!extension_isvalid(filename))
		crit_error("Scene description:", "invalid extension!", NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
	{
		crit_error("Scene description:", "file open error:", strerror(errno));
		return (err);
	}
	error = build_scenedata(scenedata, fd);
	if (close(fd) < 0)
		crit_error("Scene description:", "file close error:", strerror(errno));
	return (error);
}
