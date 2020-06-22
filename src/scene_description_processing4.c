/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_processing4.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 19:08:32 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/22 19:10:11 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void	destroy_elements(char **elements)
{
	int ctr;

	ctr = 0;
	while (elements[ctr] != NULL)
	{
		free(elements[ctr]);
		ctr++;
	}
	free(elements);
}

int		count_elements(char **elements)
{
	int ctr;

	ctr = 0;
	while (elements[ctr] != NULL)
		ctr++;
	return (ctr);
}

t_bool	element_only_has_numbers(char **elements)
{
	int i;
	int j;

	i = 1;
	while (i < 3)
	{
		j = 0;
		while (elements[i][j])
		{
			if (!ft_isdigit(elements[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
