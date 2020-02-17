

#include "cub3d.h"

t_bool	keyhandler(int keystate, t_cub3d *cub3d)
{
	if (keystate == KB_W)
		move_forward(cub3d->raycast, cub3d);
	else if (keystate == KB_S)
		move_backward(cub3d->raycast, cub3d);
	else if (keystate == KB_A)
		rotate_left(cub3d->raycast, cub3d);
	else if (keystate == KB_D)
		rotate_right(cub3d->raycast, cub3d);
	else
		return (false);
	return (true);
}
