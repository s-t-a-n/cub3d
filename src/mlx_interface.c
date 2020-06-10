/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_interface.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 15:55:32 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:21:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** write a pixel to an image
*/

void			mlx_wpixel(t_mlx_image *mlximage, t_vector2 pos, int color)
{
	*(unsigned int *)(mlximage->addr + (pos.x * (mlximage->bpp / 8) + pos.y
				* mlximage->line_size)) = color;
}

/*
** write a rectangular to an image
*/

void			mlx_wrect(t_mlx_image *mlximage, t_vector2 pos,
					t_vector2 size, int color)
{
	int		xctr;

	while (size.y > 0)
	{
		xctr = 0;
		while (xctr < size.x)
		{
			mlx_wpixel(mlximage, pos, color);
			pos.x++;
			xctr++;
		}
		pos.x -= xctr;
		pos.y++;
		size.y--;
	}
}

/*
** read pixel color from texture
*/

unsigned int	mlx_rpixel(t_vector2 pos, t_mlx_text_image *texture)
{
	return (*(unsigned int *)(texture->addr + (pos.x * (texture->bpp / 8)
				+ pos.y * texture->line_size)));
}
