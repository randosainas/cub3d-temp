/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:37:59 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/01 21:21:19 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

/*			Calculate distance of perpendicular ray (
			Euclidean distance would give fisheye effect!)*/
/*
@glance				compute distance to wall from a point where an imainary
					ray is perpendicular to two planes (camera plane and
					imaginary player position plane) where where these 2 planes
			   		are parallel to eachother.
@ray.side_x or y	has an additioal incremental distance prior the hit, that 
					needs to be substracted to get the distance to the hit wall
@line_h				line height to be drawn on the screen is inversly
					releated to window height. The closer the player to a wall
					the higher the vertical line on the screen to be drawn.
*/

static void	dist_to_wall(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.p_wall_dist = (data->ray.side_x - data->ray.delta_x);
	else
		data->ray.p_wall_dist = (data->ray.side_y - data->ray.delta_y);
	//Calculate height of line to draw on screen
//	if (fabs(data->ray.p_wall_dist) < 1e-8)//double is 0
//		data->ray.p_wall_dist = 1;//display the wall to max height
	data->ray.line_h = (int)(WIN_HEIGHT / data->ray.p_wall_dist);
//	printf("ray.side_x %f, ray.side_y %f, ray.delta_x %f, ray.delta_y %f, perWallDist %f, lineH %d\n",
///	data->ray.side_x, data->ray.side_y, data->ray.delta_x, data->ray.delta_y, data->ray.p_wall_dist, data->ray.line_h);
 
	//calculate lowest and highest pixel to fill in current stripe
	/*printf("side %d, dist %f, side_x %f, delta_x %f, side y %f, delta_y %f \n",
			data->ray.side,  data->ray.p_wall_dist, data->ray.side_x, data->ray.delta_x,
			data->ray.side_y, data->ray.delta_y);*/
	data->ray.line_start = -data->ray.line_h / 2 + WIN_HEIGHT / 2;
	if (data->ray.line_start < 0)
		data->ray.line_start = 0;
	data->ray.line_end = data->ray.line_h / 2 + WIN_HEIGHT / 2;
	if (data->ray.line_end >= WIN_HEIGHT)
		data->ray.line_end = WIN_HEIGHT - 1;
}

/*
@glance		each wall will have a different texture. substact to get
			to the data->textures[] array position in init_textures(). so 
@if, else	North, east, south, west facing texture.
*/

static void	assign_texture_to_wall(t_data *data)
{
	if (data->ray.side == 0 && data->ray.x < 0)
		data->ray.tex_nr = (data->map[data->ray.map_x][data->ray.map_y] - 49);
	else if (data->ray.side == 1 && data->ray.y > 0)
		data->ray.tex_nr = (data->map[data->ray.map_x][data->ray.map_y] - 48);
	else if (data->ray.side == 0 && data->ray.x > 0)
		data->ray.tex_nr = (data->map[data->ray.map_x][data->ray.map_y] - 47); 
	else if (data->ray.side == 1 && data->ray.y < 0)
		data->ray.tex_nr = (data->map[data->ray.map_x][data->ray.map_y] - 46);
}

static void	comp_textures(t_data *data)
{
	assign_texture_to_wall(data);
	//calculate value of data->ray.wallX
	//where exactly the wall was hit 
	if (data->ray.side == 0) 
			data->ray.wallX = data->player.y_i + data->ray.p_wall_dist * data->ray.y;
		else
			data->ray.wallX = data->player.x_i + data->ray.p_wall_dist * data->ray.x;
		data->ray.wallX -= floor((data->ray.wallX));
			      //x coordinate on the texture
		data->ray.texX = (int)(data->ray.wallX * (double)TEXTURE_W);
		if ((data->ray.side == 0 && data->ray.x > 0))
//				(data->ray.side == 1 && data->ray.y < 0))
			data->ray.texX = TEXTURE_W - data->ray.texX -1;
		if (data->ray.side == 1 && data->ray.y < 0)
			data->ray.texX = TEXTURE_W - data->ray.texX -1;

      // How much to increase the texture coordinate per screen pixel
	data->ray.step = 1.0 * TEXTURE_H / data->ray.line_h;
      // Starting texture coordinate
	data->ray.texPos = (data->ray.line_start - WIN_HEIGHT /
			2 + data->ray.line_h / 2) * data->ray.step;
}
/*
@glance		cast one ray per each pixel on window width.
			comp distance from player to a hit wall. Fill one screen
			column pixel by pixel.
@texture	.......TODO
*/

void	cast_rays(t_data *data)
{
	int color;
	int y;
	int i;
	
	i = 0;
	while (i < WIN_WIDTH)
    {
		scale_pos_dir(data, i);
		comp_ray_side_step(data);
		move_along_ray_dda(data);
		dist_to_wall(data);	
		comp_textures(data);
		y = data->ray.line_start;
		while (y < data->ray.line_end)
     	{
 // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			data->ray.texY = (int)data->ray.texPos & (TEXTURE_H - 1);
			data->ray.texPos += data->ray.step;
//		color = ORANGE;// + TEXTURE_W + data->texY + data->ray.texX;
			color = data->textures[data->ray.tex_nr][TEXTURE_W * data->ray.texY + data->ray.texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (data->ray.side == 1)
				color = (color >> 1) & 8355711;
			pixel_put(&data->img, i, y, color);
			y++;
		}
//	printf("---------------------------Column on screen %d data->ray.line_start %d data->ray.line_end %d\n", i, data->ray.line_start, data->ray.line_end);
		i++;
	}
//	printf("End of loop %d\n", x);
}
