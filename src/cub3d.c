/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:16 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 00:08:18 by sverschu      ########   odam.nl         */
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

int	execute_rendering(t_scenedata *scenedata, t_player *player,
		t_bool save_frame)
{
	t_mlx	mlx;
	if(!mlx_construct(&mlx, scenedata->resolution, SELF_NAME))
		return (err);

	mlx_key_hook(mlx.window, &keyhook, &mlx);
	mlx_expose_hook(mlx.window, &exposehook, &mlx);
	mlx_hook(mlx.window, 17, 0L, &shutdown, NULL);
	return(mlx_loop(mlx.backend));
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
	t_bool		save_frame;

	save_frame = false;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		save_frame = true;
	else if (argc != 2)
		crit_error("Cube3d:", "Come back later with better arguments", NULL);
	if (construct_scenedata(&scenedata, argv[1]) == noerr
			&& construct_game(&scenedata, &player) == noerr)
			return (execute_rendering(&scenedata, &player, save_frame));
	else
		return (SELF_ERROR);
}
