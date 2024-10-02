/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:37:59 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/02 20:06:30 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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
@utart & end		highest and lowest pixel of a screen pixcel column.
*/

static void	dist_to_wall(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.p_wall_dist = (data->ray.side_x - data->ray.delta_x);
	else
		data->ray.p_wall_dist = (data->ray.side_y - data->ray.delta_y);
	if (data->ray.p_wall_dist < 1e-6)
		data->ray.p_wall_dist = 1e-6;
	data->ray.line_h = (int)(WIN_HEIGHT / data->ray.p_wall_dist);
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

/*
@glance		calc the x-axis value of a point (hit_wall_x) where this ray 
			hit the wall.
@ray.step	for every pixel on the screen, what is the step of pixel change
			on the texture.
			texture is small like 60pixels and the line is like 600 pixels,
			so 10 pixels will be the same color on the screen.
@tex_pos	calc start position for texture on y-axis, which pixel to take
			from texture file.
@future		consider the reason why casting to int is not the same as floor()
*/

static void	comp_textures(t_data *data)
{
	assign_texture_to_wall(data);
	if (data->ray.side == 0)
		data->ray.hit_wall_x = data->player.y_i
			+ data->ray.p_wall_dist * data->ray.y;
	else
		data->ray.hit_wall_x = data->player.x_i
			+ data->ray.p_wall_dist * data->ray.x;
	data->ray.hit_wall_x -= floor(data->ray.hit_wall_x);
	data->ray.tex_x = (int)(data->ray.hit_wall_x * (double)TEXTURE_W);
	if ((data->ray.side == 0 && data->ray.x > 0))
		data->ray.tex_x = TEXTURE_W - data->ray.tex_x -1;
	if (data->ray.side == 1 && data->ray.y < 0)
		data->ray.tex_x = TEXTURE_W - data->ray.tex_x -1;
	data->ray.step = 1.0 * TEXTURE_H / data->ray.line_h;
	data->ray.tex_pos = (data->ray.line_start - WIN_HEIGHT
			/ 2 + data->ray.line_h / 2) * data->ray.step;
}

/*
@glance		cast one ray per each pixel on window width.
			comp distance from player to a hit wall. Fill one screen
			column pixel by pixel.
@tex_y		cast texture to int and mask to protect overflow.
@if			bitshift and mask to create illusion of shading, decresing each
			color value.
			>> 1 10000000 (128) becomes 01000000 (64) ie division by 2.
			& 8355711 is 0x7f7f7f masking assures color in 0-255 range. 
*/

void	cast_rays(t_data *data)
{
	int	color;
	int	y;
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		scale_pos_dir(data, i);
		comp_ray_side_step(data);
		move_along_ray_dda(data);
		dist_to_wall(data);
		comp_textures(data);
		y = data->ray.line_start;
		while (y++, y < data->ray.line_end)
		{
			data->ray.tex_y = (int)data->ray.tex_pos & (TEXTURE_H - 1);
			data->ray.tex_pos += data->ray.step;
			color = data->textures[data->ray.tex_nr]
			[TEXTURE_W * data->ray.tex_y + data->ray.tex_x];
			if (data->ray.side == 1)
				color = (color >> 1) & 8355711;
			pixel_put(&data->img, i, y, color);
		}
		i++;
	}
}
