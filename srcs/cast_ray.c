/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:13:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/08/24 21:15:43 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static double	slope_l(t_data *data, double x2, double y2)
{
	double	k;

	(void)data;
	k = y2 / x2;
//	k = (y2 data->player.y)/(x2 - data->player.x);
	return (k);
}

static int	line_eq_y(t_data *data, double k, double x)
{
	return (k*(x - data->player.x) + data->player.y);
}

static void	draw_ray(t_data *data, double x_d, double y_d)
{
	int	i;
	double slope;
	double y;
	static int	j = 0;

	i = 0;
	slope = slope_l(data, x_d, y_d);
	y = line_eq_y(data, slope, data->player.x);
	while (i < data->m_cell_size * (- x_d))
	{
//		printf(" %ld %f %f \n", data->player.x - i, y, slope); 	
		pixel_put(&data->img, data->player.x - i, y, GREEN);
		i++;
		y -= slope;
	}
	data->ray_dist = sqrtf((powf(x_d, 2)) +
				powf((y_d), 2)) * data->m_cell_size;
	printf("no %d has a distance of %f pixels\n", j++, data->ray_dist);
//	if (data->map[(int)((data->player.x - i - 1)/data->m_cell_size)]
//			[(int)(y / data->m_cell_size)] == '1')
//		return (1);
//	else
//		return (0);
}

static	int hit_wall(t_data *data, double x_d, double y_d)
{
	if (x_d != 0.000000 && y_d != 0.000000)
		if ((data->map[(int)((data->player.y + y_d * data->m_cell_size - 1 - data->m_start_y)/data->m_cell_size)][(int)((data->player.x + x_d)/data->m_cell_size)]) == '1')
		{
			printf("WALL Found\n");	
			draw_ray(data, x_d, y_d);
//			calc_ray_distance
			return (0);
		}
	printf("no hit x_d %f, y_d %f\n", x_d, y_d);
	return (1);
}

/*
 *not using vectors since the ray degree does not change, one ray until wall
 hit.
 *
 * spawning pos 270, H_FOW 30, first ray 240deg.
 * ray crossing with the next y axis is x = 1 (ie one cell on 2Dmap). this
 * is tan30
 *
@tan		tan(alpha) = x_d / y_d 
 * */

void	cast_ray(t_data *data)
{
	double	x_d;
	double	y_d;
	double	ray_angle;//radian
	int	i;

	ray_angle = H_FOV * PI/180;
	i = 1;
	while (ray_angle >= 0.00000001)// - H_FOV * PI/180)
	{
		i = 1;
		x_d = 0;
		y_d = 0;	
		while (hit_wall(data, x_d, y_d))
		{
			x_d = -1 * i;//vertical line crossing
			y_d = x_d / tan(ray_angle);
//			printf("x_d %f y_d: %f\n", x_d, y_d);
			if (y_d < -1.00000000)
			{	
				y_d = -1 * i;//horisontal line crossing
				x_d = y_d * tan(ray_angle);
			}
//			printf("x_d %f y_d: %f\n", x_d, y_d);
//	printf("map_start_y %d\n", data->map_start_y);
			printf("wall check@ y: %d x: %d \n",
			(int)((data->player.y + y_d * data->m_cell_size - data->m_start_y)/data->m_cell_size), (int)((data->player.x + x_d)/data->m_cell_size));
			i++;
		}
		printf("ray angle %f\n", ray_angle);
		ray_angle -= PI/180;
	}
//	if (data->map[(int)((data->player.y + y_d - 1)/data->m_cell_size)]
//			[(int)((data->player.x + x_d)/data->m_cell_size)] == '1')
//		printf("WALL Found\n");
// nd second point, find line equation?
//	if (draw_ray(data, x_d, y_d))
//		printf("wall found\n");
//	if (check_wall(y - 1))
//	if (check_wall(y + 1))
//	printf("half FOW is %d\n", H_FOV);
	}	
