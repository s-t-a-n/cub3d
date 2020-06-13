/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp1.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 17:11:01 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:11:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void			destruct_bmpimage(t_bmpimage *image)
{
	free(image->data);
	free(image);
}

t_bool			write_bmpimage(int fd, t_bmpimage *image)
{
	return (write(fd, &image->header, 54) != -1
			&& write(fd, image->data, image->datasize) != -1);
}
