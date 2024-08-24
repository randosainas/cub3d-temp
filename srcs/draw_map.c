/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:49 by rsainas           #+#    #+#             */
/*   Updated: 2024/08/23 17:47:38 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
@glance		get null term double char array size, max chars and no of lines
*/

void	map_size(t_data *data)
{
	int i;
	int j;
	char **temp;
	
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
static void	draw_player_eye(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < rect_h)
	{
		j = 0;
		while (j < rect_w)
		{		
			pixel_put(&data->img, data->player.x + j,
					data->player.y + i, BLACK);
			j++;
		}
		i++;
	}
}*/

static int	draw_player(t_data *data, int y, int x, int start_y)
{

	if (data->map[y][x] == 'N')
	{		
		data->player.x = x * data->m_cell_size;
		data->player.y = start_y + y * data->m_cell_size;
		return (ORANGE);
	}
//		return (draw_payer_eye(data, int y, int x), ORAGE);
	return (BLUE);
}

/*
@glance		print a rectangel, get left corner cordinates
*/

void	draw_map_cell(t_data *data, int left_x, int left_y, int color)
{
	int	i;
	int j;

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
@glance		print a miniature 2D map
*/

void	draw_map(t_data *data)
{
	int x;
	int y;
	int color;


	data->m_cell_size = (int)(0.5 * WIN_WIDTH / data->map_w);
	data->m_start_y = WIN_HEIGHT - (data->m_cell_size * data->map_h);	
	y = 0;
	color = WHITE;
	while (x = 0, data->map[y] && y < data->map_h)
	{
		while (x < data->map_w)
		{
			if(data->map[y][x] == '1')
				color = BLACK;
			else if(data->map[y][x] == '0')
				color = GREY;
			else
				color = draw_player(data, y, x, data->m_start_y);
			draw_map_cell(data, x * data->m_cell_size,
				data->m_start_y + y * data->m_cell_size, color);
			x++;
		}
		y++;
	}
	printf("existance %d, player pos x %ld y %ld, face %d, cell %d\n",
			data->player.player_found,
			data->player.x, data->player.y, data->player.face, data->m_cell_size);
}
