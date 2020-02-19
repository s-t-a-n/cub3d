/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:14:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/18 18:38:16 by sverschu      ########   odam.nl         */
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


/*
** global defines
*/
# define SELF_NAME "Stan's Cub3d"
# define SELF_ERROR 1

/*
** raycasting defines
*/
# define PLAYER_DEF_ROT_SPEED 0.03
# define PLAYER_DEF_MOVE_SPEED 0.05
# define COLLISION_WALL_MP 1.7
# define COLLISION_WALL_SLIDE 0.5
/*
** map defines
*/
# define MAP_APROX_LINE_COUNT 20

# define MAP_RAYHIT '*'
# define MAP_WALKABLE 'X'
# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_ITEM '2'

/*
** keycodes and X events
*/

# define KB_DEFAULT 0

# define X_EVENT_KEYDOWN 2
# define X_EVENT_KEYRELEASE 3
# define X_EVENT_MOUSEDOWN 4
# define X_EVENT_MOUSERELEASE 5
# define X_EVENT_MOUSEMOVE 6
# define X_EVENT_EXIT 1

# define X_MASK_KEYDOWN 1L<<0
# define X_MASK_KEYRELEASE 1L<<1

# ifdef OSX
#  define KB_W 13
#  define KB_A 0
#  define KB_S 1
#  define KB_D 2
#  define KB_ARR_UP 126
#  define KB_ARR_LEFT 123
#  define KB_ARR_DOWN 125
#  define KB_ARR_RIGHT 124
#  define KB_ESC 53
# endif

# ifdef LINUX
#  define KB_W 119
#  define KB_A 97
#  define KB_S 115
#  define KB_D 100
#  define KB_ARR_UP 65362
#  define KB_ARR_LEFT 65361
#  define KB_ARR_DOWN 65364
#  define KB_ARR_RIGHT 65363
#  define KB_ESC 65307
# endif

/*
** keyhandling related datatypes
*/

typedef enum	e_key_flag
{
	kb_w_flag = 1<<0,
	kb_a_flag = 1<<1,
	kb_s_flag = 1<<2,
	kb_d_flag = 1<<3,
	kb_arr_up_flag = 1<<4,
	kb_arr_left_flag = 1<<5,
	kb_arr_down_flag = 1<<6,
	kb_arr_right_flag = 1<<7
}				t_key_flag;

/*
** scenedata related datatypes
*/

typedef enum	e_direction
{
	north = 0,
	east = 1,
	south = 2,
	west = 3
}				t_direction;

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
	t_flvector2	pos;
	t_flvector2	vdir;
    float	mov_speed;
    float	rot_speed;
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
	t_mlx_image	*image_nact;
	void		*backend;
	void		*window;
	unsigned int	keystate;
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
	t_raycast	*raycast;
	t_bool		save_frame;
	t_bool		first_render;
}				t_cub3d;

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
t_bool			construct_game(t_cub3d *cub3d);
int				game_update(t_cub3d *cub3d);

/*
** game_meta.c
*/
void			convert_edirection_to_flvector2(t_direction dir,
					t_flvector2 *vdir);

/*
** mlx_interface.c
*/
void			 mlx_wpixel(t_mlx_image mlximage, t_vector2 pos, int color);
void			 mlx_wrect(t_mlx_image mlximage, t_vector2 pos, t_vector2 size, int color);
t_bool			 mlx_construct(t_mlx *mlx, t_vector2 resolution, char *window_name);
t_mlx			 *mlx_destruct(t_mlx *mlx);

/*
** mlx_hooks.c
*/
int				keydown(int keycode, t_cub3d *cub3d);
int				keyrelease(int keycode, t_cub3d *cub3d);
int				exposehook(int exposecode, t_mlx *mlx);

/*
** mlx_rendering.c
*/
int				render_frame(t_cub3d *cub3d);
void			clear_image(t_mlx *mlx);

/*
** mlx_generic.c
*/

unsigned int    trgb(int t, int r, int g, int b);

/*
** raycaster.c
*/
t_bool			raycaster(t_raycast *raycast, t_cub3d *cub3d);

/*
** raycaster_initialisation.c
*/
void			init_raycast(t_raycast *raycast, t_cub3d *cub3d);

/*
** raycaster_keyhandling.c
*/
void			move_forward(t_raycast *raycast, t_cub3d *cub3d);
void			move_backward(t_raycast *raycast, t_cub3d *cub3d);
void			move_left(t_cub3d *cub3d);
void			move_right(t_cub3d *cub3d);
void			rotate_left(t_raycast *raycast, t_cub3d *cub3d);
void			rotate_right(t_raycast *raycast, t_cub3d *cub3d);

/*
** keyhandler.c
*/
t_bool			keyhandler(int keystate, t_cub3d *cub3d);
void			keystate_setflag(unsigned int *keystate, int keycode);
void			keystate_unsetflag(unsigned int *keystate, int keycode);
/*
** cub3d.c
*/
void			crit_error(char *head, char *body, char *tail);
void			clean_shutdown(t_cub3d *cub3d);

#endif
