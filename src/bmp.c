/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:49:17 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:12:39 by sverschu      ########   odam.nl         */
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
	bmpheader.bits_per_pixel = mlx_image->bpp;
	bmpheader.image_size_bytes = image->datasize;
	return (bmpheader);
}

static unsigned int	rpixel_rev(t_vector2 pos, t_mlx_image *image)
{
	unsigned int	p;

	p = *(unsigned int *)(image->addr + (pos.x * (image->bpp / 8)
		+ pos.y * image->line_size));
	return (p);
}

static void			wpixel(unsigned char *data, int line_size,
							t_vector2 pos, unsigned int color)
{
	*(unsigned int *)(data + (pos.x * 4 + pos.y * line_size)) = color;
}

static void			conv_to_bmpformat(unsigned char *dst, t_mlx_image *image)
{
	t_vector2	pos;
	t_vector2	wpos;

	pos.y = image->resolution.y - 1;
	wpos.y = 0;
	while (pos.y > 0)
	{
		pos.x = image->resolution.x - 1;
		wpos.x = image->resolution.x - 1;
		while (pos.x > 0)
		{
			wpixel(dst, image->line_size, wpos, rpixel_rev(pos, image));
			pos.x--;
			wpos.x--;
		}
		wpos.y++;
		pos.y--;
	}
}

unsigned char		*construct_bmpdata(t_bmpimage *image,
						t_mlx_image *mlx_image)
{
	unsigned char *data;

	image->datasize = (mlx_image->resolution.x * mlx_image->resolution.y)
		* (mlx_image->bpp / 8);
	ft_printf("construct_bmpdata: datasize: %lu\n", image->datasize);
	data = malloc(image->datasize);
	if (data)
	{
		conv_to_bmpformat(data, mlx_image);
		return (data);
	}
	else
	{
		return (NULL);
		crit_error("MALLOC", strerror(errno), NULL);
	}
}
