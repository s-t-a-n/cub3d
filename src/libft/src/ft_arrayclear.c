/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrayclear.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:28:24 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/10 19:28:32 by sverschu      ########   odam.nl         */
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
