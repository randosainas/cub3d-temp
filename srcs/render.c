/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:22:23 by rsainas           #+#    #+#             */
/*   Updated: 2024/08/15 09:46:11 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
@glance 	bytes are not alligned line_len differs from WIN_WIDTH therfore
			calc memory offset by using mlx_get_img_addr function
*/

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static	void	is_pixel_bounded(t_data *data, int x, int y, double ratio)
{
	(void)ratio;
	pixel_put(&data->img, x, y, WHITE);
}

/*
@glance			iterate through all pixels on window, for each pixel
				call ...
@mlx			here all pixels have color on the image, put image to window.
*/

int	render(t_data *data)
{
	int		x;
	int		y;
	double	ratio;

	y = -1;
	ratio = WIN_WIDTH / 4;
	while (y++ < WIN_HEIGHT)
	{
		x = -1;
		while (x++ < WIN_WIDTH)
			is_pixel_bounded(data, x, y, ratio);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
