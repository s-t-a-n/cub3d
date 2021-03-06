/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_initialisation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 16:55:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/18 22:42:33 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx		*mlx_destruct(t_mlx *mlx)
{
	return (mlx);
}

void		mlx_initialise_textures(t_mlx *mlx, t_scenedata *scenedata)
{
	int		i;

	i = 0;
	while (i < TEXTURE_STOCK + (scenedata->textured_floor_and_ceiling ? 2 : 0)
			+ scenedata->extra_sprites)
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
		mlx->images[i].img = mlx_new_image(mlx->backend,
				scenedata->resolution.x, scenedata->resolution.y);
		mlx->images[i].resolution = scenedata->resolution;
		if (mlx->images[i].img)
		{
			mlx->images[i].addr = mlx_get_data_addr(mlx->images[i].img,
				&mlx->images[i].bpp, &mlx->images[i].line_size,
				&mlx->images[i].endian);
			if (!mlx->images[i].addr)
				crit_error("mlx:",
						"failed to get image address for image buffer!", NULL);
		}
		else
			crit_error("mlx:", "failed to create image buffer!",
						NULL);
		i++;
	}
	mlx->image_nact_i = 0;
	mlx->image_nact = &mlx->images[mlx->image_nact_i];
}

static void	check_resolution_overflow(t_mlx *mlx, t_vector2 *res)
{
	t_vector2 max_res;

	mlx_get_screen_size(mlx->backend, &max_res.x, &max_res.y);
	if (res->x > max_res.x)
		res->x = max_res.x;
	if (res->y > max_res.y)
		res->y = max_res.y;
	mlx->resolution = *res;
}

void		mlx_initialise(t_mlx *mlx, t_scenedata *scenedata,
				char *window_name)
{
	mlx->backend = mlx_init();
	mlx->resolution = scenedata->resolution;
	mlx->keystate = KB_DEFAULT;
	if (mlx->backend)
	{
		check_resolution_overflow(mlx, &scenedata->resolution);
		mlx->window = mlx_new_window(mlx->backend, scenedata->resolution.x,
				scenedata->resolution.y, window_name);
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
