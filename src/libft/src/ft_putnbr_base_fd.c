/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base_fd.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:58:57 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:58:58 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(unsigned long nb, int base, int fd)
{
	const char ctab[36] = "0123456789abcdefghijklmnopqrstuvwxyz";

	if (base < 2 || base > 36)
		return ;
	if (nb > (unsigned long)(base - 1))
		ft_putnbr_base_fd(nb / base, base, fd);
	ft_putchar_fd(ctab[nb % base], fd);
}
