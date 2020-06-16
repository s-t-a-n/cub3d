/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_read_from_file.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 18:07:22 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/16 21:23:05 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

void			dump_scenedata_map(t_scenedata *scenedata)
{
	size_t	ctr;

	ft_printf("---------------------------------------\n");
	ctr = 0;
	while (ctr < scenedata->map->element_count)
	{
		dump_scenedata_map_printl((char *)scenedata->map->mem[ctr]);
		ctr++;
	}
	ft_printf("---------------------------------------\n");
}
