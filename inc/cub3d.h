/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 20:10:36 by sverschu      ########   odam.nl         */
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

# ifndef MAP_APROX_LINE_COUNT
#  define MAP_APROX_LINE_COUNT 20
# endif

# ifndef MAP_PATH_DESIGNATOR
#  define MAP_PATH_DESIGNATOR 'X'
# endif

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

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

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
	int			error;
}				t_scenedata;


/*
** read_scene_description_file.c
*/
t_scenedata		*get_scenedata(char *filename);
void			crit_error(char *head, char *body, char *tail);
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
#endif
