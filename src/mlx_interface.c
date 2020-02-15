/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_interface.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 15:55:32 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 18:49:21 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** write a rectangular to an image
*/

void	mlx_wrect(t_mlx_image mlximage, t_vector2 pos,
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
** write a pixel to an image
*/

void	mlx_wpixel(t_mlx_image mlximage, t_vector2 pos, int color)
{
	*(unsigned int *)(mlximage.addr + (pos.x * (mlximage.bpp / 8) + pos.y
				* mlximage.line_size)) = color;
}

t_mlx	*mlx_destruct(t_mlx *mlx)
{
	return (mlx);
//	if (mlx->image_a)
//		mlx_destroy_image(mlx->backend, mlx->image_a);
//	if (mlx->image_b)
//		mlx_destroy_image(mlx->backend, mlx->image_b);
//	if (mlx->window)
//		mlx_destroy_window(mlx->backend, mlx->window);
//	return (NULL);
}

t_bool		mlx_construct(t_mlx *mlx, t_vector2 resolution, char *window_name)
{
	mlx->backend = mlx_init();
	mlx->resolution = resolution;
	if (mlx->backend)
	{
		mlx->window = mlx_new_window(mlx->backend, resolution.x, resolution.y,
				window_name);
		if (mlx->window)
		{
			mlx->image_a.img = mlx_new_image(mlx->backend, resolution.x,
					resolution.y);
			mlx->image_b.img = mlx_new_image(mlx->backend, resolution.x,
					resolution.y);
			mlx->image_a.addr = mlx_get_data_addr(mlx->image_a.img,
		&mlx->image_a.bpp, &mlx->image_a.line_size, &mlx->image_a.endian);
			mlx->image_b.addr = mlx_get_data_addr(mlx->image_b.img,
		&mlx->image_b.bpp, &mlx->image_b.line_size, &mlx->image_b.endian);
			mlx->image_act = &mlx->image_a;
			if (mlx->image_a.addr && mlx->image_b.addr)
				return (noerr);
			else
				crit_error("mlx:", "failed to create frames!", NULL);
		}
		else
				crit_error("mlx:", "failed to create window!", NULL);
	}
	else
		crit_error("mlx:", "failed to create connection to graphical backend!",
				NULL);
	return (err);
}
