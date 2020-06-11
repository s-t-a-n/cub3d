/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp_wrapper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 19:55:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/11 19:58:16 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

t_bool		write_bmp_from_mlx_image(t_mlx_image *mlx_image)
{
	bmpimage	*image;
	int			fd;

	image = malloc(sizeof(bmpimage));
	if (image)
	{
		// open
		// construct
		if (!write_bmpimage(fd, image))
		{
			close_file(fd);
			crit_error("write_bmp_from_mlx_image", "couldnt generate bmp!", NULL);
		}
		else
		{
			close_file(fd);
			return (true);
		}
	}
	else
		crit_error("MALLOC", strerror(errno), NULL);
	return (false);
}
