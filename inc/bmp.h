/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 18:41:31 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/18 21:23:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <string.h>
# include <stdint.h>
# include "cub3d.h"
# include "ft_std.h"

/*
** Source: https://engineering.purdue.edu/
**			ece264/16au/hw/HW13#
**			:~:text=The%20structure%20of
**			%20the%20BMP,red%2C%20green%2C%20and%20blue.
*/

# define BMPHEADER_SIZE			54

/*
** pragma pack needed to disable byte alignment optimisation
** (to make sure it is actually 54 and not 56 bytes)
*/
# pragma pack(push, 1)

typedef struct					s_bmpheader
{
	uint16_t					type;
	uint32_t					size;
	uint16_t					reserved1;
	uint16_t					reserved2;
	uint32_t					offset;
	uint32_t					dib_header_size;
	int32_t						width_px;
	int32_t						height_px;
	uint16_t					num_planes;
	uint16_t					bits_per_pixel;
	uint32_t					compression;
	uint32_t					image_size_bytes;
	int32_t						x_resolution_ppm;
	int32_t						y_resolution_ppm;
	uint32_t					num_colors;
	uint32_t					important_colors;
}								t_bmpheader;

typedef struct					s_bmpimage
{
	t_bmpheader					header;
	unsigned char				*data;
	size_t						datasize;
	int							padding;
	int							linesize;
}								t_bmpimage;

# pragma pack(pop)

/*
** bmp.c
*/

void							destruct_bmpimage(t_bmpimage *image);
t_bool							write_bmpimage(int fd, t_bmpimage *image);
t_bmpheader						construct_bmpheader(t_bmpimage *image,
									t_mlx_image *mlx_image);
unsigned char					*construct_bmpdata(t_bmpimage *image,
									t_mlx_image *mlx_image);

/*
** bmp_wrapper.c
*/

t_bool							write_bmp_from_mlx_image(t_mlx_image *mlx_image,
									char *fname);
#endif
