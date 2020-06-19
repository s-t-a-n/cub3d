/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putwchar_fd.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 21:59:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/19 21:59:13 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <unistd.h>
#include "libft.h"

/*
** https://en.m.wikipedia.org/wiki/UTF-8
** -> if ascii, put normally
** -> if number of significant bits exceed ascii (2^8 is set),
** handle second byte and so forth up until 4 bytes(UTF-8).
** to extract byte values in order to put them, the value is shifted forward
** and corrected for non-significant bits
*/

void	ft_putwchar_fd(wchar_t wc, int fd)
{
	if (wc <= 0x7F)
		ft_putchar_fd(wc, fd);
	else if (wc <= 0x7FF)
	{
		ft_putchar_fd((wc >> 0x6) + 0xC0, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar_fd((wc >> 0xC) + 0xE0, fd);
		ft_putchar_fd(((wc >> 0x6) & 0x3F) + 0x80, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 0x10FFFF)
	{
		ft_putchar_fd((wc >> 0x12) + 0xF0, fd);
		ft_putchar_fd(((wc >> 0xc) & 0x3F) + 0x80, fd);
		ft_putchar_fd(((wc >> 0x6) & 0x3F) + 0x80, fd);
		ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
}
