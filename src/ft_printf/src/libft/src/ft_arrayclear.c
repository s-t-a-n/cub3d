/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptr_array_clear.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu </var/mail/sverschu>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 17:41:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 00:08:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_arrayclear(void **ptr_array, size_t len)
{
	if (!ptr_array)
		return (NULL);
	while (len > 0)
	{
		free(ptr_array[len - 1]);
		len--;
	}
	free(ptr_array);
	return (NULL);
}
