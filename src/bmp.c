/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:49:17 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/12 18:20:14 by sverschu      ########   odam.nl         */
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
	return (write(fd, &image->header, 54) != -1 && write(fd, image->data, image->datasize) != -1);
}

t_bmpheader		construct_bmpheader(t_bmpimage *image, t_mlx_image *mlx_image)
{
	t_bmpheader bmpheader;

	ft_memset(&bmpheader, 0, sizeof(t_bmpheader));
	bmpheader.type = 0x4d42;

	bmpheader.size = 174;


	//bmpheader.size = image->datasize + 54;
	bmpheader.offset = 54;
	bmpheader.dib_header_size = 40;
	bmpheader.width_px = mlx_image->resolution.x;
	bmpheader.height_px = mlx_image->resolution.y;
	bmpheader.num_planes = 1;
	bmpheader.bits_per_pixel = mlx_image->bpp;
	//bmpheader.image_size_bytes = image->datasize;

	ft_printf("bpp: %i\n", mlx_image->bpp);
	return (bmpheader);
	(void)image;
}

unsigned char	*construct_bmpdata(t_bmpimage *image, t_mlx_image *mlx_image)
{
	unsigned char *data;

	image->datasize = 0;
	return(NULL);

	image->datasize = (mlx_image->resolution.x * mlx_image->resolution.y) * (mlx_image->bpp/8);
	ft_printf("construct_bmpdata: datasize: %lu\n", image->datasize);
	data = malloc(image->datasize);
	ft_memcpy(data, mlx_image->addr, image->datasize);
	//memset(data, 0, image->datasize);
	return(data);


	(void)mlx_image;
	return (malloc(1));
}
