/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:49 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/02 19:39:39 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
@glance		get null term double char array size, max chars and no of lines
*/

void	map_size(t_data *data)
{
	int		i;
	int		j;
	char	**temp;

	data->map_w = 0;
	data->map_h = 0;
	temp = data->map;
	i = 0;
	while (temp[i] != NULL)
	{
		data->map_h++;
		j = 0;
		while (temp[i][j] != '\0')
			j++;
		if (data->map_w < j)
			data->map_w += j;
		i++;
	}
}

/*
@glance		print a rectangel, get left corner cordinates
*/

void	draw_map_cell(t_data *data, int left_x, int left_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->m_cell_size)
	{
		j = 0;
		while (j++ < data->m_cell_size)
			pixel_put(&data->img, i + left_x, j + left_y, color);
		i++;
	}
}

/*
@glance		convert an int color struct to base hex color number
			and bitshift to each color to one RGB integer.
*/

signed int	color_base_hex( t_color color)
{
	if (color.r < 0)
		color.r = 0;
	if (color.r > 255)
		color.r = 255;
	if (color.g < 0)
		color.g = 0;
	if (color.g > 255)
		color.g = 255;
	if (color.b < 0)
		color.b = 0;
	if (color.b > 255)
		color.b = 255;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

/*
@glance		print a miniature 2D map
*/

void	draw_ceiling_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j++ < WIN_WIDTH)
			pixel_put(&data->img, j, i, color_base_hex(data->ceiling));
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j++ < WIN_WIDTH)
			pixel_put(&data->img, j, i, color_base_hex(data->floor));
		i++;
	}
}

/*
@glance		print a miniature 2D map
*/

void	draw_map(t_data *data)
{
	int	x;
	int	y;
	int	color;

	data->m_cell_size = (int)(0.25 * WIN_WIDTH / data->map_w);
	data->m_start_y = WIN_HEIGHT - (data->m_cell_size * data->map_h);
	y = 0;
	color = WHITE;
	while (data->map[y] && y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (data->map[y][x] == '1')
				color = BLACK;
			else if (data->map[y][x] == '0')
				color = GREY;
			if (y == (int)(data->player.x_i) && x == (int)(data->player.y_i))
				color = GREEN;
			draw_map_cell(data, x * data->m_cell_size,
				data->m_start_y + y * data->m_cell_size, color);
			x++;
		}
		y++;
	}
}
