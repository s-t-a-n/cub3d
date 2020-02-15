/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:14:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/15 19:39:04 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <errno.h>
# include <math.h>

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
** raycasting defines
*/
#define PLAYER_ROT_SPEED 5.0
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
** raycasting related dataypes
*/
typedef struct  s_raycast
{
    t_flvector2 dir;    //direction of ray
    t_vector2   pos;    // pos of current ray
  	t_flvector2	camplane;
  	t_flvector2 campos;
    t_vector2   tilestep; //dependent on quadrant either 1 or -1 to get to next intersection
    t_flvector2 intercept; //delta x and y from player
    t_flvector2 delta_intercept; //delta x and y from player
    t_bool      hit;
    int 		side;
    float       distance; // distance till hit
    t_vector2   phaser; //counts one up for every pixel
}               t_raycast;

/*
** game datatypes
*/
typedef struct	s_player
{
	t_vector2	pos;
	t_flvector2	dpos;
	t_flvector2	vdir;
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
	int		bpp;
	int		line_size;
	int		endian;
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
	t_vector2	resolution;
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

typedef struct	s_cub3d
{
	t_scenedata	*scenedata;
	t_mlx		*mlx;
	t_player	*player;
	t_bool		save_frame;
	t_bool		first_render;
}				t_cub3d;

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
t_bool  construct_game(t_cub3d *cub3d, t_scenedata *scenedata);

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
** mlx_rendering.c
*/
int		render_frame(t_cub3d *cub3d);
void	clear_image(t_mlx *mlx);

/*
** mlx_generic.c
*/

unsigned int    trgb(int t, int r, int g, int b);
int				shutdown(int code, void *ptr);

/*
** raycaster.c
*/
t_bool	raycaster(t_cub3d *cub3d);

/*
** raycaster_initialisation.c
*/
void	init_raycast(t_raycast *raycast, t_cub3d *cub3d);
#endif
