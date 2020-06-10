/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:29:36 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:29:37 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isprint(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || ft_issymbol(c));
}
