/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:26:28 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/13 20:06:14 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isprint(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || ft_issymbol(c));
}
