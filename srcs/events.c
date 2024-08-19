/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:30:17 by rsainas           #+#    #+#             */
/*   Updated: 2024/08/15 18:21:45 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_data *data)
{
	ft_putstr_fd("EXIT", 1);
	ft_putstr_fd(", Window X pressed.\n", 1);
	ft_exit(data);
	exit (EXIT_SUCCESS);
}

/*
@glance			clear all calloc and malloced by mlx
*/

void	ft_exit(t_data *data)
{	
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}


