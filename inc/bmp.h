/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:47:58 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/12 17:50:03 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <string.h>
# include "cub3d.h"
# include "ft_std.h"

/*
** Source: https://engineering.purdue.edu/ece264/16au/hw/HW13#:~:text=The%20structure%20of%20the%20BMP,red%2C%20green%2C%20and%20blue.
*/

# define BMPHEADER_SIZE			54

typedef struct					s_bmpheader {		// Total: 54 bytes
	uint16_t					type;				// Magic identifier: 0x4d42
	uint32_t					size;				// File size in bytes
	uint16_t					reserved1;			// Not used
	uint16_t					reserved2;			// Not used
	uint32_t					offset;				// Offset to image data in bytes from beginning of file (54 bytes)
	uint32_t					dib_header_size;	// DIB Header size in bytes (40 bytes)
	int32_t 					width_px;			// Width of the image
	int32_t 					height_px;			// Height of image
	uint16_t					num_planes;			// Number of color planes
	uint16_t					bits_per_pixel;		// Bits per pixel
	uint32_t					compression;		// Compression type
	uint32_t					image_size_bytes;	// Image size in bytes
	int32_t 					x_resolution_ppm;	// Pixels per meter
	int32_t 					y_resolution_ppm;	// Pixels per meter
	uint32_t					num_colors;			// Number of colors
	uint32_t					important_colors;	// Important colors
}								t_bmpheader;

typedef struct					s_bmpimage {
	t_bmpheader					header;
	unsigned char				*data;
	size_t						datasize;
	int							padding;
}								t_bmpimage;

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
