/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_std.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 18:44:55 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/22 19:17:23 by sverschu      ########   odam.nl         */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#endif
