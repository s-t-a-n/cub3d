/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 17:16:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/06 20:48:47 by sverschu      ########   odam.nl         */
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

typedef struct	s_map
{
				
}				t_map;


/*
** read_scene_description_file.c
*/
t_scenedata *get_scenedata(char *filename);


#endif
