/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:58:37 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/01 11:20:45 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
@glance		a positive data->rot rotates counterclockwise and negative
			clockwise.
*/

#include "cub3D.h"

static void	key_strafe(int key, t_data *data)
{
	if (key == 0x61)//a
	{
		if (data->map[(int)(data->player.x_i - data->ray.plane_x * data->step)]
				[(int)data->player.y_i] == '0' &&
				data->map[(int)data->player.x_i][(int)(data->player.y_i -
				data->ray.plane_y * data->step)]  == '0')
		{
			data->player.x_i -= data->ray.plane_x * data->step;
			data->player.y_i -= data->ray.plane_y * data->step;
		}
	}
	if (key == 0x64)//d
	{
		if (data->map[(int)(data->player.x_i + data->ray.plane_x * data->step)]
				[(int)data->player.y_i] == '0' &&
				data->map[(int)data->player.x_i][(int)(data->player.y_i +
				data->ray.plane_y * data->step)]  == '0')
		{
			data->player.x_i += data->ray.plane_x * data->step;
			data->player.y_i += data->ray.plane_y * data->step;
		}
	}
}


static void	key_r_l(int key, t_data *data)
{
	double temp_player_x;
	double temp_plane_x;

	temp_player_x = data->ray.player_x;
	temp_plane_x = data->ray.plane_x;

	if (key == 0xff51)//left
	{
		data->ray.player_x = data->ray.player_x * cos(data->rot) -
			data->ray.player_y * sin(data->rot);
		data->ray.player_y = temp_player_x * sin(data->rot) +
			data->ray.player_y * cos(data->rot);
		data->ray.plane_x = data->ray.plane_x * cos(data->rot) -
			data->ray.plane_y * sin(data->rot);
		data->ray.plane_y = temp_plane_x * sin(data->rot) + 
			data->ray.plane_y * cos(data->rot);
	}
	if (key == 0xff53)//right
	{
		data->ray.player_x = data->ray.player_x * cos(-data->rot) -
			data->ray.player_y * sin(- data->rot);
		data->ray.player_y = temp_player_x * sin(-data->rot) +
			data->ray.player_y * cos(- data->rot);
		data->ray.plane_x = data->ray.plane_x * cos(-data->rot) -
			data->ray.plane_y * sin(- data->rot);
		data->ray.plane_y = temp_plane_x * sin(-data->rot) + 
			data->ray.plane_y * cos(-data->rot);
	}
}

	
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
	if (key == 0xff1b)
	{
		ft_putstr_fd(", ESC key pressed.\n", 1);
//		ft_exit(head);//TODO cleaning
		exit (EXIT_SUCCESS);
	}
	if (key == 0x77 || key == 0xff52)//w up
	{			
//		printf("I want to take this step x %f, int x %d, int y %d, map %c\n",
//					(data->player.x_i + data->ray.player_x * data->step),
//					(int)(data->player.x_i + data->ray.player_x * data->step),
//					(int)data->player.y_i,
//					data->map[(int)(data->player.x_i + data->ray.player_x * data->step)]
//					[(int)data->player.y_i]);
//		printf("w pressed\n");//adding a step towards the direction
		if (data->map[(int)(data->player.x_i + data->ray.player_x * data->step)]
				[(int)data->player.y_i] == '0')
		{
//			printf("player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
//			printf("after step: player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
			data->player.x_i += data->ray.player_x * data->step;
		}
//		else
//			printf("cannot move, player to-be pos x %d, y %y \n", data->player.x_i, data->player_y_i)
		if (data->map[(int)data->player.x_i][(int)(data->player.y_i +
				data->ray.player_y * data->step)]  == '0')
			data->player.y_i += data->ray.player_y * data->step;
	}
	if (key == 0x73 || key == 0xff54)//s down
	{
	//	printf("s pressed\n");
		if (data->map[(int)(data->player.x_i - data->ray.player_x * data->step)]
				[(int)data->player.y_i] == '0')
		{
//			printf("player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
			data->player.x_i -= data->ray.player_x * data->step;
//			printf("after step: player inital x %d player diretional ray.player_x %f\n", data->player.x_i, data->ray.player_x);
		}
		if (data->map[(int)data->player.x_i][(int)(data->player.y_i -
				data->ray.player_y * data->step)]  == '0')
			data->player.y_i -= data->ray.player_y * data->step;
	}
	key_strafe(key, data); 
	key_r_l(key, data);
	render(data);
	return (0);
}
