/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_issymbol.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:29:45 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:29:50 by sverschu      ########   odam.nl         */
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
