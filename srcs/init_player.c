/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:30 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/01 17:54:36 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	assign_dir_plane_vectors_add(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'S')
	{
		data->ray.player_x = 1;	
		data->ray.player_y = 0;
		data->ray.plane_x = 0;
		data->ray.plane_y = -0.66;
	}
	if (data->map[y][x] == 'W')
	{
		data->ray.player_x = 0;	
		data->ray.player_y = -1;
		data->ray.plane_x = -0.66;
		data->ray.plane_y = 0;
	}
}

/*
@glance		in case spawn position in North, there is no movement on plane
			x axis and player y axis, since these vectors are perpendicular
			to each other.
*/

static void	assign_dir_plane_vectors(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'N')
	{
		data->ray.player_x = -1;
		data->ray.player_y = 0;
		data->ray.plane_x = 0;//no movement along x-axis	
		data->ray.plane_y = 0.66;

	}
	if (data->map[y][x] == 'E')
	{
		data->ray.player_x = 0;
		data->ray.player_y = 1;
		data->ray.plane_x = 0.66;
		data->ray.plane_y = 0;
	}
	assign_dir_plane_vectors_add(data, y, x);
}

/*
@glance		itialize the player position out of rendering loop
@0.51		a initialization offset for the FOV to be in the center of
			a square a player is spawn
*/

void	init_player_pos(t_data *data)
{
	int x;
	int y;

	y = 0;
	map_size(data);
	while (x = 0, data->map[y] && y < data->map_h)
	{
		while (x < data->map_w) 
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'E' ||
				data->map[y][x] == 'S' || data->map[y][x] == 'W')
			{		
				data->player.x_i = y + 0.51;
				data->player.y_i = x + 0.51;
				assign_dir_plane_vectors(data, y, x);
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
