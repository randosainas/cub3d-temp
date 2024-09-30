/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:03:12 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/30 19:37:24 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	malloc_failure(void)
{
	ft_putstr_fd("Malloc error!\n", 1);
	perror("Malloc from mlx libarary failed.");
	exit(EXIT_FAILURE);
}

/*
@ft_strcmp		a check of operating system since MacOs does not use
				mlx_destroy_display function.
*/

static	void	pixel_addr_init(t_data *data)
{
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
//		if (ft_strncmp(OS, "Linux", 5) == 0)
			mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
}

static	void	data_init(t_data *data)
{
	(void)data;
}

/*
@glance			register 3 hooks on keys and mouse.
*/

static	void	events_init(t_data *data)
{	
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_stroke, data);
	init_player_pos(data);
	data->step = 0.50;
	data->rot = 0.2;
	data->ray.player_x = -1;
	data->ray.player_y = 0;
	data->ray.plane_x = 0;
	data->ray.plane_y = 0.66;

//	mlx_mouse_hook(data->win, mouse_roll, data);
}

/*
@glance			initate or free in case allocation fails
*/

void	init_graphics(t_data *data)
{	
	data->mlx = mlx_init();
	if (!data->mlx)
		malloc_failure();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, data->name);
	if (!data->win)
	{
//		if (ft_strncmp(OS, "Linux", 5) == 0)
			mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{	
		mlx_destroy_window(data->mlx, data->win);
//		if (ft_strncmp(OS, "Linux", 5) == 0)
			mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
	pixel_addr_init(data);
	data_init(data);
	events_init(data);
}
