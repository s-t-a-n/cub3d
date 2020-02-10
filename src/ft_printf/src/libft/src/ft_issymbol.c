/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_issymbol.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 20:05:03 by sverschu      #+#    #+#                 */
/*   Updated: 2019/11/13 20:05:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_issymbol concerns all characters which are not alphanumeric but printable
** like !@#$%^&* and stuff
*/

int		ft_issymbol(int c)
{
	return ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) ||
			(c >= 91 && c <= 96) || (c >= 123 && c <= 126));
}
