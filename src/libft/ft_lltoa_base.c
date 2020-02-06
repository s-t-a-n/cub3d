/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lltoa_base.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/19 22:35:25 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/21 19:40:31 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

char			*ft_lltoa_base(long long int nb, int base, int uppercase)
{
	char *str;
	char *finstr;

	if (base < 2 || base > 36)
		return (ft_strdup(""));
	if (nb < 0)
	{
		nb *= -1;
		str = ft_ulltoa_base(nb, base, uppercase);
		if (str)
		{
			finstr = ft_strjoin("-", str);
			free(str);
			return (finstr);
		}
		else
			return (NULL);
	}
	else
		return (ft_ulltoa_base(nb, base, uppercase));
}
