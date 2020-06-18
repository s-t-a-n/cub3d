/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:49:17 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/18 22:41:45 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

t_bmpheader			construct_bmpheader(t_bmpimage *image,
						t_mlx_image *mlx_image)
{
	t_bmpheader bmpheader;

	ft_memset(&bmpheader, 0, sizeof(t_bmpheader));
	bmpheader.type = 0x4d42;
	bmpheader.size = image->datasize + 54;
	bmpheader.offset = 54;
	bmpheader.dib_header_size = 40;
	bmpheader.width_px = mlx_image->resolution.x;
	bmpheader.height_px = mlx_image->resolution.y;
	bmpheader.num_planes = 1;
	bmpheader.bits_per_pixel = 24;
	bmpheader.image_size_bytes = image->datasize;
	return (bmpheader);
}

static unsigned int	rpixel(t_vector2 pos, t_mlx_image *image)
{
	return (*(unsigned int *)(image->addr + (pos.x * (image->bpp / 8)
		+ pos.y * image->line_size)));
}

static void			wpixel(unsigned char *data, int line_size,
							t_vector2 pos, unsigned int color)
{
	ft_memcpy(data + (pos.x * 3 + pos.y * line_size), &color, 3);
}

static void			conv_to_bmpformat(unsigned char *dst, t_mlx_image *image,
							int linesize)
{
	t_vector2	rpos;
	t_vector2	wpos;

	rpos.y = image->resolution.y;
	wpos.y = 0;
	while (rpos.y >= 0)
	{
		rpos.x = image->resolution.x;
		wpos.x = image->resolution.x;
		while (rpos.x >= 0)
		{
			wpixel(dst, linesize, wpos, rpixel(rpos, image));
			rpos.x--;
			wpos.x--;
		}
		wpos.y++;
		rpos.y--;
	}
}

unsigned char		*construct_bmpdata(t_bmpimage *image,
						t_mlx_image *mlx_image)
{
	unsigned char *data;

	image->padding = mlx_image->resolution.x % 4;
	image->linesize = mlx_image->resolution.x * 3 + image->padding;
	image->datasize = (mlx_image->resolution.y * image->linesize * 5);
	data = malloc(image->datasize);
	if (data)
	{
		conv_to_bmpformat(data, mlx_image, image->linesize);
		return (data);
	}
	else
	{
		crit_error("MALLOC", strerror(errno), NULL);
		return (NULL);
	}
}
