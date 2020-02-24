/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_initialisation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 16:55:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/24 17:04:31 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx   *mlx_destruct(t_mlx *mlx)
{
	return (mlx);
	//  if (mlx->image_a)
	//      mlx_destroy_image(mlx->backend, mlx->image_a);
	//  if (mlx->image_b)
	//      mlx_destroy_image(mlx->backend, mlx->image_b);
	//  if (mlx->window)
	//      mlx_destroy_window(mlx->backend, mlx->window);
	//  return (NULL);
}

void		mlx_initialise_textures(t_mlx *mlx, t_scenedata *scenedata)
{
	int		i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		mlx->textures[i].img = mlx_xpm_file_to_image(mlx->backend,
			scenedata->f_textures[i], &mlx->textures[i].size.x,
			&mlx->textures[i].size.y);
		if (mlx->textures[i].img)
		{
			mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img,
				&mlx->textures[i].bpp, &mlx->textures[i].line_size,
				&mlx->textures[i].endian);
			if (!mlx->textures[i].addr)
				crit_error("mlx:", "failed to get image address for:",
						scenedata->f_textures[i]);
		}
		else
			crit_error("mlx:", "failed to create image for texture file:",
					scenedata->f_textures[i]);
		i++;
	}
}

void		mlx_initialise_images(t_mlx *mlx, t_scenedata *scenedata)
{
	int		i;

	i = 0;
	while (i < IMAGE_COUNT)
	{
		mlx->images[i].img = mlx_new_image(mlx->backend, scenedata->resolution.x, scenedata->resolution.y);
		if (mlx->images[i].img)
		{
			mlx->images[i].addr = mlx_get_data_addr(mlx->images[i].img,
				&mlx->images[i].bpp, &mlx->images[i].line_size,
				&mlx->images[i].endian);
			if (!mlx->images[i].addr)
				crit_error("mlx:", "failed to get image address for image buffer",
						NULL);
		}
		else
			crit_error("mlx:", "failed to create image buffer:",
						NULL);
		i++;
	}
	mlx->image_nact_i = 0;
	mlx->image_nact = &mlx->images[mlx->image_nact_i];
}
/*
void		mlx_initialise_images(t_mlx *mlx, t_scenedata *scenedata)
{
	mlx->image_a.img = mlx_new_image(mlx->backend, scenedata->resolution.x,
			scenedata->resolution.y);
	mlx->image_b.img = mlx_new_image(mlx->backend, scenedata->resolution.x,
			scenedata->resolution.y);
	if (mlx->image_a.img && mlx->image_b.img)
	{
		mlx->image_a.addr = mlx_get_data_addr(mlx->image_a.img,
			&mlx->image_a.bpp, &mlx->image_a.line_size, &mlx->image_a.endian);
		mlx->image_b.addr = mlx_get_data_addr(mlx->image_b.img,
			&mlx->image_b.bpp, &mlx->image_b.line_size, &mlx->image_b.endian);
		mlx->image_nact = &mlx->image_a;
		mlx->image_act = &mlx->image_b;
		if (mlx->image_a.addr && mlx->image_b.addr)
			mlx_initialise_textures(mlx, scenedata);
		else
			crit_error("mlx:", "failed to create images!", NULL);
	}

	// testing
	mlx->image_c.img = mlx_new_image(mlx->backend, scenedata->resolution.x, scenedata->resolution.y);
	mlx->image_c.addr = mlx_get_data_addr(mlx->image_c.img, &mlx->image_c.bpp, &mlx->image_c.line_size, &mlx->image_c.endian);
}
*/

void      mlx_initialise(t_mlx *mlx, t_scenedata *scenedata, char *window_name)
{
	mlx->backend = mlx_init();
	mlx->resolution = scenedata->resolution;
	mlx->keystate = KB_DEFAULT;
	if (mlx->backend)
	{
		mlx->window = mlx_new_window(mlx->backend, scenedata->resolution.x, scenedata->resolution.y,
				window_name);
		if (mlx->window)
		{
			mlx_initialise_images(mlx, scenedata);
			mlx_initialise_textures(mlx, scenedata);
		}
		else
			crit_error("mlx:", "failed to create window!", NULL);
	}
	else
		crit_error("mlx:", "failed to create connection to graphical backend!",
				NULL);
}
