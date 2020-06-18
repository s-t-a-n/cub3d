/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:51:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/18 18:20:43 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

t_bool	open_file(char *path, int *fd)
{
	*fd = open(path, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
	return (*fd > -1);
}

t_bool	close_file(int fd)
{
	return (close(fd) == 0);
}

t_bool	write_to_file(int fd, unsigned char *buf, size_t count)
{
	return (write(fd, buf, count) != -1);
}
