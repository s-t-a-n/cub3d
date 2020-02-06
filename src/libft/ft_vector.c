/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vector.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 18:57:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/06 19:17:02 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

unsigned char	*vector_destroy(t_vector *vec)
{
	unsigned char *str;

	str = vec->mem;
	free(vec);
	return (str);
}

t_vector		*vector_init(size_t element_cap, size_t element_size)
{
	t_vector *vec;

	vec = malloc(sizeof(vec));
	if (vec)
	{
		vec->mem = ft_calloc(element_cap, element_size);
		if (!(vec->mem))
		{
			free(vec);
			return (NULL);
		}
		vec->element_size = element_size;
		vec->element_cap = element_cap;
		vec->element_count = 0;
	}
	return (vec);
}

t_vector		*vector_grow(t_vector *vec)
{
	t_vector *newvec;

	newvec = vector_init(vec->element_cap * 2, vec->element_size);
	if (newvec)
	{
		ft_memcpy(newvec->mem, vec->mem,
				vec->element_count * vec->element_size);
		newvec->element_count = vec->element_count;
	}
	vector_destroy(vec);
	return (newvec);
}

int				vector_pushback(t_vector *vec, unsigned char *element)
{
	if (vec->element_count == vec->element_cap)
		vec = vector_grow(vec);
	if (vec)
	{
		ft_memcpy(vec->mem + (vec->element_count * vec->element_size),
				element, vec->element_size);
		(vec->element_count)++;
		return (noerr);
	}
	return (err);
}

/*
** pet project for later
** int	vector_pushfront(vector *vec, void *element)
** {
**
** }
*/
