/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:30 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/19 17:22:12 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
@glance		itialize the player position out of rendering loop
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
				data->player.x_i = y;
				data->player.y_i = x;
			}
			x++;
		}
		y++;
	}
}
