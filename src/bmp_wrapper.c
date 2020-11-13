/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp_wrapper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 19:55:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/18 19:27:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "bmp.h"

t_bool		write_bmp_from_mlx_image_norm0(t_mlx_image *mlx_image,
											char *fname,
											t_bmpimage *image,
											int *fd)
{
	if (open_file(fname, fd))
	{
		image->data = construct_bmpdata(image, mlx_image);
		image->header = construct_bmpheader(image, mlx_image);
		if (!write_bmpimage(*fd, image))
		{
			destruct_bmpimage(image);
			close_file(*fd);
			crit_error("write_bmp_from_mlx_image",
					"couldnt generate bmp!", NULL);
		}
		else
		{
			destruct_bmpimage(image);
			close_file(*fd);
			return (TRUE);
		}
	}
	else
	{
		destruct_bmpimage(image);
		crit_error("write_bmp_from_mlx_image",
				"couldnt open file for writing", NULL);
	}
	return (FALSE);
}

t_bool		write_bmp_from_mlx_image(t_mlx_image *mlx_image, char *fname)
{
	t_bmpimage	*image;
	int			fd;

	image = ft_calloc(1, sizeof(t_bmpimage));
	if (image)
	{
		if (write_bmp_from_mlx_image_norm0(mlx_image, fname, image, &fd))
			return (TRUE);
	}
	else
	{
		crit_error("MALLOC", strerror(errno), NULL);
		return (FALSE);
	}
	return (FALSE);
}
