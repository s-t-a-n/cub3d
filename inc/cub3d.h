/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/08 21:31:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>

// DONT FUCKING FORGET TO REMOVE THIS LIB
# include <stdio.h>

# include "get_next_line.h"
# include "libft.h"

/*
** Scene description datastruct
*/

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
	char		*map;
	int			error;
}				t_scenedata;

/*
** read_scene_description_file.c
*/
t_scenedata		*get_scenedata(char *filename);
void			pscene_error(char *errordesc);


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

#endif
