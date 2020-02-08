/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_description_verification.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 18:36:50 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/08 22:16:11 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	scenedesc_verify_resolution(t_scenedata *scenedata)
{
	t_bool error;
	
	error = (!(scenedata->resolution.x <= 0
			|| scenedata->resolution.x > 5120
			|| scenedata->resolution.y <= 0
			|| scenedata->resolution.y > 2880));
	if (error == err)
		pscene_error("resolution was not set or is malformed!");
	//printf("OK: scenedesc: resolution is %i by %i\n", scenedata->resolution.x, scenedata->resolution.y);
	return (error);
}

t_bool	scenedesc_verify_textures(t_scenedata *scenedata)
{
	return (scenedata != NULL);
}

t_bool	scenedesc_verify_colors(t_scenedata *scenedata)
{
	return (scenedata == NULL);
}

t_bool	scenedesc_verify_map(t_scenedata *scenedata)
{
	return (scenedata != NULL);
}
