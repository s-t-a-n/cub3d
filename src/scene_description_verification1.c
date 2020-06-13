/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification1.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 17:07:57 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/13 17:08:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

t_bool			scenedesc_verify_resolution(t_scenedata *scenedata)
{
	t_bool error;

	error = (!(scenedata->resolution.x <= 0
			|| scenedata->resolution.x > 5120
			|| scenedata->resolution.y <= 0
			|| scenedata->resolution.y > 2880));
	if (error == err)
		crit_error("Scene description:",
				"resolution was not set or is malformed!", NULL);
	return (error);
}
