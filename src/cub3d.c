/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:16 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/15 19:39:40 by sverschu      ########   odam.nl         */
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

int	execute_rendering(t_cub3d *cub3d)
{
	t_mlx	mlx;

	cub3d->mlx = &mlx;
	if(!mlx_construct(cub3d->mlx, cub3d->scenedata->resolution, SELF_NAME))
		return (err);
	mlx_key_hook(cub3d->mlx->window, &keyhook, &cub3d->mlx);
	mlx_expose_hook(cub3d->mlx->window, &exposehook, &cub3d->mlx);
	mlx_hook(cub3d->mlx->window, 17, 0L, &shutdown, NULL);
	//mlx_loop_hook(cub3d->mlx->backend, &render_frame, cub3d);
	cub3d->first_render = true;
	render_frame(cub3d);
	return(mlx_loop(cub3d->mlx->backend));
}

/*
	save_frame = 0;
	t_vector2 pos; pos.x = 100; pos.y = 100;
	t_vector2 size; size.x = 20; size.y = 200;
	int	color = trgb(0, 255, 0, 0);

	//mlx_wpixel(mlx.image_a, pos, color);
	mlx_wrect(mlx.image_a, pos, size, color);
	mlx_put_image_to_window(mlx.backend, mlx.window, mlx.image_a.img,0,0);
*/

int		main(int argc, char **argv)
{
	t_scenedata	scenedata;
	t_player	player;
	t_cub3d		cub3d;

	cub3d.player = &player;
	cub3d.scenedata = &scenedata;

	cub3d.save_frame = false;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		cub3d.save_frame = true;
	else if (argc != 2)
		crit_error("Cube3d:", "Come back later with better arguments", NULL);
	if (construct_scenedata(&scenedata, argv[1]) == noerr
			&& construct_game(&cub3d, &scenedata) == noerr)
			return (execute_rendering(&cub3d));
	else
		return (SELF_ERROR);
}
