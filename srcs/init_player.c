/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:30 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/30 19:26:02 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			if (data->map[y][x] == 'N')
			{		
				data->player.x_i = y + 0.51;
				data->player.y_i = x + 0.51;
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
