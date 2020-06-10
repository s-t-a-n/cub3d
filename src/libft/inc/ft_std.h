/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_std.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 18:44:55 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:30:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STD_H
# define FT_STD_H

typedef enum		e_bool
{
	false = 0,
	err = 0,
	true = 1,
	noerr = 1
}					t_bool;

typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_flvector2
{
	double			x;
	double			y;
}					t_flvector2;

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#endif
