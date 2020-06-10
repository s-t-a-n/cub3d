/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:14:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:11:14 by sverschu      ########   odam.nl         */
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
** graphical defines
*/
# define IMAGE_COUNT 100

/*
** texture defines
*/
# define TEXTURE_CAP				50
# define TEXTURE_STOCK				5

# define TEXT_N						0
# define TEXT_E						1
# define TEXT_S						2
# define TEXT_W						3
# define TEXT_SP					4
# define TEXT_FL					5
# define TEXT_CE					6
# define TEXT_SPE					7

/*
** raycasting defines
*/
# define PLAYER_DEF_ROT_SPEED 0.1
# define PLAYER_DEF_MOVE_SPEED 0.2
# define WALL_SIZE_MP 1.0
# define COLLISION_WALL_MP 1.7
# define VW_ANGLE 0.66

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
	west = 3,
	nodir = 4
}				t_direction;

typedef struct			s_sprite
{
	int					distance;
	t_flvector2			pos;
	int					item;
}						t_sprite;

/*
** raycasting related dataypes
*/
typedef struct  s_raycast
{
    t_vector2			phaser; //counts one up for every pixel on x-axis
    t_vector2			pos;    // pos of current ray
    t_vector2			tilestep; //dependent on quadrant either 1 or -1 to get to next intersection
    t_flvector2			dir;    //direction of ray
    t_flvector2			camplane;
    t_flvector2			campos;
    t_flvector2			intercept; //delta x and y from player
    t_flvector2			delta_intercept; //delta x and y from player
    t_bool				hit;
    t_bool				side;
	int					item;
    double				distance; // distance till hit
	double				zbuffer[2048]; // freaking random
	int					spritecount;
	t_sprite			sprites[100]; // even more so, freaking random
}						t_raycast;

/*
** game datatypes
*/
typedef struct	s_player
{
	t_flvector2		pos;
	t_flvector2		vdir;
	double			mov_speed;
	double			rot_speed;
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
	void			*img;
	char			*addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_bool			active;
}				t_mlx_image;

typedef struct	s_mlx_text_image
{
	void			*img;
	char			*addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_vector2	size;
}				t_mlx_text_image;

typedef struct	s_texture_draw_op
{
	t_vector2		image_pos;
	t_vector2		texture_pos;
	t_vector2		size;
	t_flvector2		step;
}				t_texture_draw_op;

typedef struct	s_mlx
{
	t_mlx_image			images[IMAGE_COUNT];
	t_mlx_text_image	textures[TEXTURE_CAP];
	t_mlx_image			*image_act;
	t_mlx_image			*image_nact;
	int					image_nact_i;
	void				*backend;
	void				*window;
	unsigned int		keystate;
	int					exposestate;
	t_vector2			resolution;
}						t_mlx;

typedef struct	s_scenedata
{
	t_vector2	resolution;
	char 		*f_textures[TEXTURE_CAP];
	t_bool		textured_floor_and_ceiling;
	int			extra_sprites;
	t_color		floor_color;
	t_color		ceiling_color;
	int			floor_trgb;
	int			ceiling_trgb;
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
t_bool			scenedesc_process_textures_sprites(t_scenedata *scenedata,
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
** mlx_initialisation.c
*/
t_mlx			*mlx_destruct(t_mlx *mlx);
void			mlx_initialise(t_mlx *mlx, t_scenedata *scenedata,
					char *window_name);

/*
** mlx_interface.c
*/
unsigned int	mlx_rpixel(t_vector2 pos, t_mlx_text_image *texture);

void			mlx_wrect_texture(t_mlx_image mlximage, t_vector2 pos,
					t_vector2 size, t_mlx_text_image texture);

void			mlx_wpixel(t_mlx_image *mlximage, t_vector2 pos, int color);
void			mlx_wrect(t_mlx_image *mlximage, t_vector2 pos, t_vector2 size,
					int color);

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
void			draw_textured_floor_and_ceiling(t_raycast *raycast, t_cub3d *cub3d);

/*
** raycaster_initialisation.c
*/
void			init_raycast(t_raycast *raycast, t_cub3d *cub3d);
void			insert_sprite(t_raycast *raycast, int x, int y, int item);

/*
** raycaster_keyhandling.c
*/
void			move_forward(char **map, t_player *player);
void			move_backward(char **map, t_player *player);
void			move_left(char **map, t_player *player);
void			move_right(char **map, t_player *player);
void			rotate_left(t_raycast *raycast, t_player *player);
void			rotate_right(t_raycast *raycast, t_player *player);

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
/*
** raycaster.c norminette slaughter
*/
typedef struct	s_draw_sprites
{
	int			i;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstartx;
	int			drawstarty;
	int			drawendx;
	int			drawendy;
	int			texx;
	int			texy;
	int			spritewidth;
	int			d;
	t_vector2	pos;
	t_vector2	tex_pos;
	unsigned int color;
	int			x;
	int			y;
	t_mlx_text_image	*texture;
}				t_draw_sprite;
typedef struct			s_draw_tex_line
{
	double				tj_step;
	double				tj;
	t_flvector2			wp;
	t_vector2			tp;
	t_vector2			ip;
	t_mlx_text_image	*te;
	int					yctr;
}						t_draw_tex_line;
typedef struct		s_draw_tex_floor_ceiling
{
	t_vector2			ctr;
	t_vector2			nctr;
	t_flvector2			ray_dir_left;
	t_flvector2			ray_dir_right;
	int					cur_y;
	double				camera_y;
	double				camera_y_rel;
	t_flvector2			floor_step;
	t_flvector2			floor;
	t_vector2			text_pos;
	t_mlx_text_image	*floor_texture;
	t_mlx_text_image	*ceiling_texture;
}					t_draw_tex_floor_ceiling;

void	dump_raycast(t_raycast *raycast);
void	calc_ray_position_and_direction(t_raycast *raycast, t_player *player);
void	calc_pos_in_cameraplane(t_raycast *raycast, t_cub3d *cub3d);
void	calc_tilestep_and_intercept(t_raycast *raycast, t_cub3d *cub3d);
void	calc_delta_intercept(t_raycast *raycast);
void	calc_distance(t_raycast *raycast, t_cub3d *cub3d);
void	perform_dda(t_raycast *raycast, t_cub3d *cub3d);
int		select_texture_for_wall(t_raycast *raycast);
t_mlx_text_image	*select_texture(t_cub3d *cub3d, t_raycast *raycast, int num);
void	draw_colored_floors_and_ceiling(t_mlx *mlx, t_scenedata *scenedata);
void	draw_textured_floor_and_ceiling_norm1(t_raycast *raycast,
				t_cub3d *cub3d, t_draw_tex_floor_ceiling *q);
void	draw_textured_floor_and_ceiling(t_raycast *raycast, t_cub3d *cub3d);
void	draw_textured_line_norm0(t_draw_tex_line *s, t_cub3d *cub3d, t_vector2 pos, double lh);
void	draw_textured_line(t_raycast *raycast, t_cub3d *cub3d, t_vector2 pos, double lh);
void	draw_colored_line(t_raycast *raycast, t_cub3d *cub3d, t_vector2 pos, double lineheight);
void	draw_line(t_raycast *raycast, t_cub3d *cub3d);
void	swap_sprites(t_raycast *raycast, int a, int b);
int		playerdistance_sprites(t_player *player, t_flvector2 pos);
void	update_sprites(t_raycast *raycast, t_cub3d *cub3d);
void	sort_sprites(t_raycast *raycast, t_cub3d *cub3d);
void	draw_sprites_norm2(t_raycast *raycast, t_cub3d *cub3d, t_draw_sprite *s);
void	draw_sprites_norm1(t_raycast *raycast, t_cub3d *cub3d, t_draw_sprite *s);
void	draw_sprites_norm0(t_raycast *raycast, t_cub3d *cub3d, t_draw_sprite *s);
void	draw_sprites(t_raycast *raycast, t_cub3d *cub3d);
t_bool	raycaster(t_raycast *raycast, t_cub3d *cub3d);
#endif
