/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:16 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/19 17:51:18 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        crit_error(char *head, char *body, char *tail)
{
    ft_putstr_fd("\e[31mError!\e[39m\n", STDERR);
    if (head)
        ft_putstr_fd(head, STDERR);
    if (body)
        ft_putstr_fd(body, STDERR);
    if (tail)
        ft_putstr_fd(tail, STDERR);
    ft_putchar_fd('\n', STDERR);
    exit(SELF_ERROR);
}

void		clean_shutdown(t_cub3d *cub3d)
{
	// clear cub3d
	cub3d = NULL;
	exit (0);
}

int	execute_rendering(t_cub3d *cub3d)
{
	t_mlx	mlx;

	cub3d->mlx = &mlx;
	mlx_initialise(cub3d->mlx, cub3d->scenedata, SELF_NAME);
	//mlx_expose_hook(cub3d->mlx->window, &exposehook, &cub3d->mlx);
	mlx_hook(cub3d->mlx->window, X_EVENT_KEYDOWN, X_MASK_KEYDOWN, &keydown, cub3d);
	mlx_hook(cub3d->mlx->window, X_EVENT_KEYRELEASE, X_MASK_KEYRELEASE, &keyrelease, cub3d);
	mlx_loop_hook(cub3d->mlx->backend, &game_update, cub3d);
	cub3d->first_render = true;
	render_frame(cub3d);
	mlx_loop(cub3d->mlx->backend);
	return (noerr);
}

int		main(int argc, char **argv)
{
	t_scenedata	scenedata;
	t_player	player;
	t_cub3d		cub3d;
	t_raycast	raycast;

	cub3d.player = &player;
	cub3d.scenedata = &scenedata;
	cub3d.raycast	= &raycast;
	cub3d.save_frame = false;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		cub3d.save_frame = true;
	else if (argc != 2)
		crit_error("Cube3d:", "Come back later with better arguments", NULL);
	if (construct_scenedata(&scenedata, argv[1]) == noerr
			&& construct_game(&cub3d) == noerr)
			return (execute_rendering(&cub3d));
	else
		return (SELF_ERROR);
}
