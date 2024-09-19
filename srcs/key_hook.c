/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:58:37 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/19 15:55:00 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
@glance			mlx loop is listening for a key stroke, if key pressed
				values are changed and the image is rendered again.
@render()		refresh the image on window
0X77	w
0X73	s
0X61	a
0X64	d
*/

int	key_stroke(int key, t_data *data)
{
	if (key == 0Xff1b)
	{
		ft_putstr_fd(", ESC key pressed.\n", 1);
//		ft_exit(head);//TODO cleaning
		exit (EXIT_SUCCESS);
	}
	if (key == 0X77)//w
	{
		printf("w pressed\n");
		if (data->map[(int)(data->player.x_i + data->ray.player_x * data->step)]
				[(int)data->player.y_i] == '0')
		{
			printf("player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
			data->player.x_i += data->ray.player_x * data->step;
			printf("after step: player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
		}
		if (data->map[(int)data->player.x_i][(int)(data->player.y_i +
				data->ray.player_y * data->step)]  == '0')
			data->player.y_i += data->ray.player_y * data->step;
	}
	if (key == 0X73)//s
	{
		printf("s pressed\n");
		if (data->map[(int)(data->player.x_i - data->ray.player_x * data->step)]
				[(int)data->player.y_i] == '0')
		{
			printf("player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
			data->player.x_i -= data->ray.player_x * data->step;
			printf("after step: player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
		}
		if (data->map[(int)data->player.x_i][(int)(data->player.y_i -
				data->ray.player_y * data->step)]  == '0')
			data->player.y_i -= data->ray.player_y * data->step;
	}

	if (key == 0Xff52)//up
		data->ray.player_x -= 0.1;

	if (key == 0Xff51)//left
		data->ray.player_y -= 0.1;
	if (key == 0Xff53)//right
		data->ray.player_y += 0.1;
	if (key == 0X3d)
		printf("3d\n");
	if (key == 0X2d)
		printf("2d\n");
	if (key == 0Xff0d)//w
		data->ray.map_y -= 1;

//	if (key == 0Xff54)//down
	render(data);
	return (0);
}

