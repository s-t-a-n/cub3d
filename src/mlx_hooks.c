/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 20:19:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/17 18:03:48 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		keydown(int keycode, t_cub3d *cub3d)
{
	//ft_printf("keydown : %i\n", keycode);
	if (keycode == KB_ESC)
		exit(0);
	cub3d->mlx->keystate = keycode;
	return(noerr);
}

int		keyrelease(int keycode, t_cub3d *cub3d)
{
	ft_printf("keyrelease : %i\n", keycode);
	cub3d->mlx->keystate = KB_DEFAULT;
	keycode = 0;
	return(noerr);
}

int		exposehook(int exposecode, t_mlx *mlx)
{
	ft_printf("exposecode: %i\n", exposecode);
	mlx->exposestate = exposecode;
	return(exposecode);
}
/*
int		keyhook(int keycode, t_mlx *mlx)
{
	ft_printf("keyhook : %i\n", keycode);
	if (keycode == KB_ESC)
		exit(0);
	mlx->keystate = keycode;
	return(keycode);
}
*/
