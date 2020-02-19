/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhandling.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 12:08:25 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/19 16:07:08 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	keyhandler(int keystate, t_cub3d *cub3d)
{
	if (keystate & kb_w_flag)
		move_forward((char **)cub3d->scenedata->map->mem, cub3d->player);
	else if (keystate & kb_s_flag)
		move_backward((char **)cub3d->scenedata->map->mem, cub3d->player);
	if (keystate & kb_a_flag)
		move_left((char **)cub3d->scenedata->map->mem, cub3d->player);
	else if (keystate & kb_d_flag)
		move_right((char **)cub3d->scenedata->map->mem, cub3d->player);
	if (keystate & kb_arr_left_flag)
		rotate_left(cub3d->raycast, cub3d->player);
	else if (keystate & kb_arr_right_flag)
		rotate_right(cub3d->raycast, cub3d->player);
	return (true);
}

void	keystate_setflag(unsigned int *keystate, int keycode)
{
	if (keycode == KB_W)
		*keystate |= kb_w_flag;
	else if (keycode == KB_A)
		*keystate |= kb_a_flag;
	else if (keycode == KB_S)
		*keystate |= kb_s_flag;
	else if (keycode == KB_D)
		*keystate |= kb_d_flag;
	else if (keycode == KB_ARR_LEFT)
		*keystate |= kb_arr_left_flag;
	else if (keycode == KB_ARR_RIGHT)
		*keystate |= kb_arr_right_flag;
}

void	keystate_unsetflag(unsigned int *keystate, int keycode)
{
	if (keycode == KB_W && *keystate & kb_w_flag)
		*keystate ^= kb_w_flag;
	else if (keycode == KB_A && *keystate & kb_a_flag)
		*keystate ^= kb_a_flag;
	else if (keycode == KB_S && *keystate & kb_s_flag)
		*keystate ^= kb_s_flag;
	else if (keycode == KB_D && *keystate & kb_d_flag)
		*keystate ^= kb_d_flag;
	else if (keycode == KB_ARR_LEFT && *keystate & kb_arr_left_flag)
		*keystate ^= kb_arr_left_flag;
	else if (keycode == KB_ARR_RIGHT && *keystate * kb_arr_right_flag)
		*keystate ^= kb_arr_right_flag;
}
