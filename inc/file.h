/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:51:31 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/11 19:52:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "cub3d.h"
# include <fcntl.h>
# include <unistd.h>

t_bool		open_file(char *path, int *fd);
t_bool		close_file(int fd);
t_bool		write_to_file(int fd, unsigned char *buf, size_t count);

#endif
