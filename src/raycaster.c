/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 17:44:20 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/07 19:22:27 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dump_raycast(t_raycast *raycast)
{
	printf("phaser:\t\t%i x %i\n",raycast->phaser.x, raycast->phaser.y);
	printf("pos:\t\t%i x %i\n",raycast->pos.x, raycast->pos.y);
	printf("tilestep:\t\t%i x %i\n",raycast->tilestep.x, raycast->tilestep.y);
	printf("phaser:\t\t%i x %i\n",raycast->phaser.x, raycast->phaser.y);
	printf("dir:\t\t%f x %f\n",raycast->dir.x, raycast->dir.y);
	printf("camplane:\t\t%f x %f\n",raycast->camplane.x, raycast->camplane.y);
	printf("campos:\t\t%f x %f\n",raycast->campos.x, raycast->campos.y);
	printf("intercept:\t\t%f x %f\n",raycast->intercept.x, raycast->intercept.y);
	printf("delta_intercept:\t\t%f x %f\n",raycast->delta_intercept.x, raycast->delta_intercept.y);
	printf("hit:\t\t%i\n",raycast->hit);
	printf("side:\t\t%i\n",raycast->side);
	printf("item:\t\t%i\n",raycast->item);
	printf("distance:\t\t%f\n",raycast->distance);
}

void	calc_pos_in_cameraplane(t_raycast *raycast, t_cub3d *cub3d)
{
	raycast->campos.y = 0.0; //vertical raycasting is not implemented 
	raycast->campos.x = 2.0 * raycast->phaser.x / cub3d->mlx->resolution.x - 1;
}

void	calc_ray_position_and_direction(t_raycast *raycast, t_player *player)
{
	raycast->pos.x = (int)player->pos.x;
	raycast->pos.y = (int)player->pos.y;
	raycast->dir.x = player->vdir.x + raycast->camplane.x * raycast->campos.x;
	raycast->dir.y = player->vdir.y + raycast->camplane.y * raycast->campos.x;
}

void	calc_tilestep_and_intercept(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->dir.x < 0)
	{
		//left quadrants
		raycast->tilestep.x = -1;
		raycast->intercept.x = (cub3d->player->pos.x - raycast->pos.x) * raycast->delta_intercept.x;
	}
	else
	{
		//right quadrants
		raycast->tilestep.x = 1;
		raycast->intercept.x = (raycast->pos.x + 1.0 - cub3d->player->pos.x) * raycast->delta_intercept.x;
	}
	if (raycast->dir.y < 0)
	{
		//upper quadrants
		raycast->tilestep.y = -1;
		raycast->intercept.y = (cub3d->player->pos.y - raycast->pos.y) * raycast->delta_intercept.y;
	}
	else
	{
		//lower quadrants
		raycast->tilestep.y = 1;
		raycast->intercept.y = (raycast->pos.y + 1.0 - cub3d->player->pos.y) * raycast->delta_intercept.y;
	}
}

void	calc_delta_intercept(t_raycast *raycast)
{
	raycast->delta_intercept.x = fabs(1.0 / raycast->dir.x);
	raycast->delta_intercept.y = fabs(1.0 / raycast->dir.y);
}

void	calc_distance(t_raycast *raycast, t_cub3d *cub3d)
{
	if (raycast->side == 0)
		raycast->distance = (raycast->pos.x - cub3d->player->pos.x + (1 - raycast->tilestep.x) / 2.0) / raycast->dir.x;
	else
		raycast->distance = (raycast->pos.y - cub3d->player->pos.y + (1 - raycast->tilestep.y) / 2.0) / raycast->dir.y;
	raycast->zbuffer[raycast->phaser.x] = raycast->distance;
}

void		perform_dda(t_raycast *raycast, t_cub3d *cub3d)
{
	while(!raycast->hit)
	{
		if (raycast->intercept.x < raycast->intercept.y)
		{
			raycast->intercept.x += raycast->delta_intercept.x;
			raycast->pos.x += raycast->tilestep.x;
			raycast->side = 0;
		}
		else
		{
			raycast->intercept.y += raycast->delta_intercept.y;
			raycast->pos.y += raycast->tilestep.y;
			raycast->side = 1;
		}
		raycast->item = cub3d->scenedata->map->mem[raycast->pos.y][raycast->pos.x];
		if (raycast->item != MAP_WALKABLE && raycast->item != MAP_ITEM)
			raycast->hit = true;
	}
}

int				select_texture_for_wall(t_raycast *raycast)
{
	if (raycast->dir.y >= 0 && raycast->side)
		return (TEXT_N);
	else if (raycast->dir.y < 0 && raycast->side)
		return (TEXT_S);
	else if (raycast->dir.x >= 0 && raycast->side == 0)
		return (TEXT_W);
	else if (raycast->dir.x < 0 && raycast->side == 0)
		return (TEXT_E);
	else
	{
		crit_error("raycast:","unknown texture!", NULL);
		return (-1);
	}
}

// add multiple sprite opt?
t_mlx_text_image *select_texture(t_cub3d *cub3d, t_raycast *raycast, int num)
{
	if (num == MAP_WALL)
		return (&cub3d->mlx->textures[select_texture_for_wall(raycast)]);
	else if (num == MAP_ITEM)
		return (&cub3d->mlx->textures[TEXT_SP]);
	else
		return (NULL);
}

void		draw_colored_floors_and_ceiling(t_mlx *mlx, t_scenedata *scenedata)
{
	t_vector2 pos;
	t_vector2 size;
	
	size.x = mlx->resolution.x;
	size.y = mlx->resolution.y / 2;
	pos.x = 0;
	pos.y = 0;
	mlx_wrect(mlx->image_nact, pos, size, scenedata->ceiling_trgb);
	pos.x = 0;
	pos.y += size.y;
	mlx_wrect(mlx->image_nact, pos, size, scenedata->floor_trgb);
}

void		draw_textured_floor_and_ceiling(t_raycast *raycast, t_cub3d *cub3d)
{
	t_vector2			ctr;
	t_flvector2			ray_dir_left;
	t_flvector2			ray_dir_right;
	int					cur_y; //p
	double				camera_y; //posZ
	double				camera_y_rel; //rowDistance
	t_flvector2			floor_step;
	t_flvector2			floor;
	t_vector2			text_pos;
	t_mlx_text_image	*floor_texture;
	t_mlx_text_image	*ceiling_texture;

	// change later
	floor_texture = &cub3d->mlx->textures[TEXT_FL];
	ceiling_texture = &cub3d->mlx->textures[TEXT_CE];

	ray_dir_left.x = cub3d->player->vdir.x - raycast->camplane.x;
	ray_dir_left.y = cub3d->player->vdir.y - raycast->camplane.y;
	ray_dir_right.x = cub3d->player->vdir.x + raycast->camplane.x;
	ray_dir_right.y = cub3d->player->vdir.y + raycast->camplane.y;

	camera_y = cub3d->mlx->resolution.y / 2;
	ctr.y = cub3d->mlx->resolution.y / 2 ;
	while (ctr.y < cub3d->mlx->resolution.y)
	{
		cur_y = ctr.y - cub3d->mlx->resolution.y / 2;
		camera_y_rel = cur_y == 0.0 ? 0.0 : camera_y / cur_y;
		floor_step.x = camera_y_rel * (ray_dir_right.x - ray_dir_left.x) / cub3d->mlx->resolution.x;
		floor_step.y = camera_y_rel * (ray_dir_right.y - ray_dir_left.y) / cub3d->mlx->resolution.x;
		floor.x = cub3d->player->pos.x + camera_y_rel * ray_dir_left.x;
		floor.y = cub3d->player->pos.y + camera_y_rel * ray_dir_left.y;
		ctr.x = 0;
		while (ctr.x < cub3d->mlx->resolution.x)
		{
			//floor
			text_pos.x = (int)fabs(floor_texture->size.x * (floor.x - (int)floor.x));
			text_pos.y = (int)fabs(floor_texture->size.y * (floor.y - (int)floor.y));
			floor.x += floor_step.x;
			floor.y += floor_step.y;
			mlx_wpixel(cub3d->mlx->image_nact, ctr, mlx_rpixel(text_pos, floor_texture));
			//ceiling
			text_pos.x = (int)fabs(ceiling_texture->size.x * (floor.x - (int)floor.x));
			text_pos.y = (int)fabs(ceiling_texture->size.y * (floor.y - (int)floor.y));
			t_vector2 nctr;
			nctr.x = ctr.x;
			nctr.y = cub3d->mlx->resolution.y - ctr.y -1;
			mlx_wpixel(cub3d->mlx->image_nact, nctr, mlx_rpixel(text_pos, ceiling_texture));
			ctr.x++;
		}
		ctr.y++;
	}
}

void		draw_textured_line(t_raycast *raycast, t_cub3d *cub3d, t_vector2 pos, double lineheight)
{
	double				tex_jump_step;
	double				tex_jump;
	t_flvector2			wall_pos;
	t_vector2			tex_pos;
	t_vector2			image_pos;
	t_mlx_text_image		*texture;
	int				yctr;

	texture = select_texture(cub3d, raycast, raycast->item);
	
	if(raycast->side == 0)
		wall_pos.x = cub3d->player->pos.y + raycast->distance * raycast->dir.y;
	else
		wall_pos.x = cub3d->player->pos.x + raycast->distance * raycast->dir.x;
	wall_pos.x -= floor(wall_pos.x);

	tex_pos.x = (int)(wall_pos.x * (double)texture->size.x);
	if (raycast->side == 0 && raycast->dir.x > 0)
		tex_pos.x = texture->size.x - tex_pos.x - 1;
	if (raycast->side == 1 && raycast->dir.y < 0)
		tex_pos.x = texture->size.x - tex_pos.x - 1;

	tex_jump_step = (double)texture->size.y / (double)lineheight;
	tex_jump = fabs(pos.y - cub3d->mlx->resolution.y / 2 + lineheight / 2) * tex_jump_step;

	yctr = pos.y;
	while(yctr < pos.y + ((lineheight > cub3d->mlx->resolution.y) ? cub3d->mlx->resolution.y : (int)lineheight))
	{
		tex_pos.y = (int)tex_jump;
		tex_jump += tex_jump_step;
		image_pos.x = pos.x;
		image_pos.y = yctr;


		// MAGIC
		int darkness = (1080 / lineheight) * 25;
		unsigned int color = mlx_rpixel(tex_pos, texture);
		color += darkness << 8*0;
		color += darkness << 8*1;
		color += darkness << 8*2;
		color += darkness << 8*3;
		mlx_wpixel(cub3d->mlx->image_nact, image_pos, color);



		//mlx_wpixel(cub3d->mlx->image_nact, image_pos, darkness + mlx_rpixel(tex_pos, texture));
		yctr++;
	}
}

void		draw_colored_line(t_raycast *raycast, t_cub3d *cub3d,
				t_vector2 pos, double lineheight)
{
	t_vector2 size;

	if (lineheight > cub3d->mlx->resolution.y)
		lineheight = cub3d->mlx->resolution.y;
	size.y = lineheight;
	size.x = 1;
	if (raycast->side)
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00C74D0F);
	else
		mlx_wrect(cub3d->mlx->image_nact, pos, size, 0x00A9410D);
}

void		draw_line(t_raycast *raycast, t_cub3d *cub3d)
{
	double lineheight;
	t_vector2 pos;
	
	lineheight = WALL_SIZE_MP * ((double)cub3d->mlx->resolution.y / raycast->distance);
	pos.y = ((double)(cub3d->mlx->resolution.y / 2.0)) - (lineheight / 2.0);
	if (pos.y < 0)
		pos.y = 0;
	pos.x = raycast->phaser.x;
	draw_textured_line(raycast, cub3d, pos, lineheight);
	//draw_colored_line(raycast, cub3d, pos, lineheight);
}


void	swap_sprites(t_raycast *raycast, int a, int b)
{
	t_sprite tmp;
	
	tmp = raycast->sprites[a];
	raycast->sprites[a] = raycast->sprites[b];
	raycast->sprites[b] = tmp;
}

int			playerdistance_sprites(t_player *player, t_flvector2 pos)
{
	return (sqrt(pow(player->pos.x - pos.x, 2)
				+ pow(player->pos.y - pos.y, 2)));
}

void	update_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < raycast->spritecount)
	{
		sprite = &raycast->sprites[i];
		sprite->distance = playerdistance_sprites(cub3d->player, sprite->pos);
		i++;
	}
}

/*
** norm failure: should use do..while
*/
void	sort_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int		i;
	t_bool	changed;

	update_sprites(raycast, cub3d);
	changed = true;
	while (changed)
	{
		changed = false;
		i = 0;
		while (i + 1 < raycast->spritecount)
		{
			if (raycast->sprites[i].distance < raycast->sprites[i + 1].distance)
			{
				swap_sprites(raycast, i, i + 1);
				changed = true;
			}
			i++;
		}
	}
}

void	draw_sprites(t_raycast *raycast, t_cub3d *cub3d)
{
	int i;
	t_mlx_text_image	*texture = select_texture(cub3d, raycast, MAP_ITEM);

	i = 0;
	while (i < raycast->spritecount)
	{
		//translate sprite position to relative to camera
		double spriteX = raycast->sprites[i].pos.x - cub3d->player->pos.x;
		double spriteY = raycast->sprites[i].pos.y - cub3d->player->pos.y;

		double invDet = 1.0 / (raycast->camplane.x * cub3d->player->vdir.y - cub3d->player->vdir.x * raycast->camplane.y); //required for correct matrix multiplication
		
		double transformX = invDet * (cub3d->player->vdir.y * spriteX - cub3d->player->vdir.x * spriteY);
		double transformY = invDet * (-raycast->camplane.y * spriteX + raycast->camplane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((cub3d->scenedata->resolution.x / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(cub3d->scenedata->resolution.y / (transformY))); //using 'transformY' instead of the real distance prevents fisheye

		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + cub3d->scenedata->resolution.y / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub3d->scenedata->resolution.y / 2;
		if(drawEndY >= cub3d->scenedata->resolution.y) drawEndY = cub3d->scenedata->resolution.y - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(cub3d->scenedata->resolution.y / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= cub3d->scenedata->resolution.x) drawEndX = cub3d->scenedata->resolution.x - 1;

		const int texWidth = texture->size.x;
		const int texHeight = texture->size.y;

		printf("drawStartX : %i, drawEndX: %i\n", drawStartX, drawEndX);
		 //loop through every vertical stripe of the sprite on screen
		for(int x = drawStartX; x < drawEndX; x++)
		{
		  int texX = (int)(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		  //the conditions in the if are:
		  //1) it's in front of camera plane so you don't see things behind you
		  //2) it's on the screen (left)
		  //3) it's on the screen (right)
		  //4) ZBuffer, with perpendicular distance
		  if(transformY > 0 && x > 0 && x < cub3d->scenedata->resolution.x && transformY < raycast->zbuffer[x])
		  {
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current x
			{
				int d = (y) * 256 - cub3d->scenedata->resolution.y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				
				//Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
				//if((color & 0x00FFFFFF) != 0) buffer[y][x] = color; //paint pixel if it isn't black, black is the invisible color
				t_vector2 pos;
				pos.x = x;
				pos.y = y;

				t_vector2 tex_pos;
				tex_pos.x = texX;
				tex_pos.y = texY;

				unsigned int color = mlx_rpixel(tex_pos, texture);
				if (color != 0x00000000)
					mlx_wpixel(cub3d->mlx->image_nact, pos, color);
				//mlx_wpixel(cub3d->mlx->image_nact, pos, 0x00000000);
				(void)texX;
				(void)texY;
			}
		  }
		  (void)texX; (void)texWidth; (void)texHeight;
		}
		i++;
	}
}

t_bool	raycaster(t_raycast *raycast, t_cub3d *cub3d)
{
	init_raycast(raycast, cub3d);
	if (cub3d->scenedata->textured_floor_and_ceiling)
		draw_textured_floor_and_ceiling(raycast, cub3d);
	else
		draw_colored_floors_and_ceiling(cub3d->mlx, cub3d->scenedata);
	while (raycast->phaser.x < cub3d->mlx->resolution.x)
	{
		raycast->hit = false;
		calc_pos_in_cameraplane(raycast, cub3d);
		calc_ray_position_and_direction(raycast, cub3d->player);
		calc_delta_intercept(raycast);
		calc_tilestep_and_intercept(raycast, cub3d);
		perform_dda(raycast, cub3d);
		calc_distance(raycast, cub3d);
		draw_line(raycast, cub3d);
		(raycast->phaser.x)++;
	}

	sort_sprites(raycast, cub3d);
	draw_sprites(raycast, cub3d);
	return (noerr);
}
