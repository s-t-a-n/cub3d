/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:14:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/13 00:22:00 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/12 16:01:50 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <errno.h>

// DONT FUCKING FORGET TO REMOVE THIS LIB
# include <stdio.h>

# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# ifndef MAP_APROX_LINE_COUNT
#  define MAP_APROX_LINE_COUNT 20
# endif

# ifndef MAP_PATH_DESIGNATOR
#  define MAP_PATH_DESIGNATOR 'X'
# endif

/*
** global defines
*/
#define SELF_NAME "Stan's Cub3d"
#define SELF_ERROR 1

/*
** graphical defines
*/
#define VW_ANGLE 66.0
#define VW_ANGLE_INC 1.0

/*
** keycodes
*/
# define KB_ESC 53

/*
** general datatypes
*/
typedef enum	e_direction
{
	north = 0,
	east = 1,
	south = 2,
	west = 3
}				t_direction;

typedef struct	s_vector2
{
	int			x;
	int			y;
}				t_vector2;

typedef struct	s_flvector2
{
	float		x;
	float		y;
}				t_flvector2;


/*
** game datatypes
*/
typedef struct	s_player
{
	t_flvector2	pos;
	t_flvector2	viewdir;
}				t_player;

/*
** all graphics related stuff
*/
typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_mlx_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_bool		active;
}				t_mlx_image;

typedef struct	s_mlx
{
	t_mlx_image	image_a;
	t_mlx_image	image_b;
	t_mlx_image	*image_act;
	void		*backend;
	void		*window;
	int			keystate;
	int			exposestate;
}				t_mlx;


typedef struct	s_scenedata
{
	t_vector2	resolution;
	char 		*f_texture_north;
	char		*f_texture_east;
	char		*f_texture_south;
	char		*f_texture_west;
	char		*f_sprite_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	t_dynmem	*map;
	t_vector2	player_position;
	t_direction	player_orientation;
	int			error;
}				t_scenedata;


/*
**	cub3d.h
*/
void			crit_error(char *head, char *body, char *tail);

/*
** read_scene_description_file.c
*/
t_bool			construct_scenedata(t_scenedata *scenedata, char *filename);
void			dump_scenedata_map(t_scenedata *scenedata);

/*
**  scene_description_processing.c
*/
t_bool			scenedesc_process_resolution(t_scenedata *scenedata,
					char *line);
t_bool			scenedesc_process_textures(t_scenedata *scenedata,
					char *line);
t_bool			scenedesc_process_colors(t_scenedata *scenedata, char *line);
t_bool			scenedesc_process_map(t_scenedata *scenedata, char *line);

/*
** scene_description_verification.c
*/
t_bool			scenedesc_verify_resolution(t_scenedata *scenedata);
t_bool			scenedesc_verify_textures(t_scenedata *scenedata);
t_bool			scenedesc_verify_colors(t_scenedata *scenedata);
t_bool			scenedesc_verify_map(t_scenedata *scenedata);
void			destroy_scenedata(t_scenedata *scenedata);

/*
** scene_description_verification_map.c
*/
t_bool			scan_map_and_find_player_position(t_scenedata *scenedata);
t_bool			check_if_player_is_enclosed(t_scenedata *scenedata);

/*
** game.c
*/
t_bool  construct_game(t_scenedata *scenedata, t_player *player);

/*
** game_meta.c
*/
void			convert_edirection_to_flvector2(t_direction dir,
					t_flvector2 *vdir);

/*
** mlx_interface.c
*/
void    mlx_wpixel(t_mlx_image mlximage, t_vector2 pos, int color);
void    mlx_wrect(t_mlx_image mlximage, t_vector2 pos, t_vector2 size, int color);
t_bool	mlx_construct(t_mlx *mlx, t_vector2 resolution, char *window_name);
t_mlx   *mlx_destruct(t_mlx *mlx);

/*
** mlx_hooks.c
*/
int     keyhook(int keycode, t_mlx *mlx);
int		exposehook(int exposecode, t_mlx *mlx);

/*
** mlx_generic.c
*/

unsigned int    trgb(int t, int r, int g, int b);
int				shutdown(int code, void *ptr);
#endif
