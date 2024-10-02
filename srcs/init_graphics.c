/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:03:12 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/02 11:41:17 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	malloc_failure(void)
{
	ft_putstr_fd("Malloc error!\n", 1);
	perror("Malloc from mlx libarary failed.");
	exit(EXIT_FAILURE);
}

static	void	pixel_addr_init(t_data *data)
{
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
}

/*
@glance			register 2 hooks one on closing and another on keys.
				initalize player position etc and payer step "length".
*/

static	void	events_init(t_data *data)
{	
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_stroke, data);
	init_player_pos(data);
	data->step = 0.5;
	data->rot = 0.2;
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
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{	
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_failure();
	}
	pixel_addr_init(data);
	init_textures(data);
	events_init(data);
}
