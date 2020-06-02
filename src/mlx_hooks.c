/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 20:19:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/02 12:40:18 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		keydown(int keycode, t_cub3d *cub3d)
{
	if (keycode == KB_ESC)
		clean_shutdown(cub3d);
	else
		keystate_setflag(&cub3d->mlx->keystate, keycode);
	return (noerr);
}

int		keyrelease(int keycode, t_cub3d *cub3d)
{
	keystate_unsetflag(&cub3d->mlx->keystate, keycode);
	return (noerr);
}

int		exposehook(int exposecode, t_mlx *mlx)
{
	mlx->exposestate = exposecode;
	return (exposecode);
}
