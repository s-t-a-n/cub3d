/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dynmem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 18:57:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/10 00:07:44 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"

void			dynmem_destroy(t_dynmem *dym)
{
	size_t	ctr;

	ctr = 0;
	while (ctr < dym->element_count)
	{
		free((dym->mem)[ctr]);
		ctr++;
	}
	free(dym);
}

t_dynmem		*dynmem_init(size_t element_cap)
{
	t_dynmem *dym;

	dym = (t_dynmem *)malloc(sizeof(t_dynmem));
	if (dym)
	{
		dym->mem = (unsigned char **)malloc((element_cap + 1) * sizeof(char *));
		if (!(dym->mem))
		{
			free(dym);
			return (NULL);
		}
		dym->element_cap = element_cap;
		dym->element_count = 0;
	}
	return (dym);
}

static t_dynmem	*dynmem_grow(t_dynmem *dym)
{
	t_dynmem	*newdym;

	newdym = dynmem_init(dym->element_cap * 2);
	if (newdym)
	{
		while (newdym->element_count < dym->element_cap)
		{
			(newdym->mem)[newdym->element_count] =
				(dym->mem)[newdym->element_count];
			(newdym->element_count)++;
		}
		free((*dym).mem);
		free(dym);
	}
	return (newdym);
}

t_bool			dynmem_pushback(t_dynmem **dym, unsigned char *element)
{
	t_dynmem *wdym;

	wdym = *dym;
	if (wdym->element_count == wdym->element_cap)
		wdym = dynmem_grow(wdym);
	if (wdym)
	{
		(wdym->mem)[wdym->element_count] = element;
		(wdym->element_count)++;
		(*dym) = wdym;
		return (noerr);
	}
	return (err);
}
