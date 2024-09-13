/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:13:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/13 11:03:42 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
@glance		the higher the slope of a ray the less pixels a ray will display, 
			lets say the slope of a ray is 1000, this is allmost a vertical line
			and to display a ray exactly they are one x coordinate pixel appart
			from eachother; so the ray might have only 2 colored pixels,
			start and end of ray. in comparison to a vertical line has
		   a lot of pixels.
*/

static void	draw_ray(t_data *data, double x_d, double y_d)
{
	double	i;
	static int	j = 0;

	i = 0;
	while (i < data->m_cell_size * (- x_d))
	{
		pixel_put(&data->img,
				data->player.x - i, data->player.y - y_d/x_d * i, GREEN);
			i += 1;
	}
	data->ray_dist = sqrtf((powf(x_d, 2)) +
				powf((y_d), 2)) * data->m_cell_size;
	printf("no %d has a distance of %f pixels\n", j++, data->ray_dist);
}

/*static void	draw_ray_xplus(t_data *data, double x_d, double y_d)
{
	double	i;
	static int	j = 0;

	i = 0;
	while (i < data->m_cell_size * ( x_d))
	{
		pixel_put(&data->img,
				data->player.x + i, data->player.y + y_d/x_d * i, GREEN);
			i += 1;
	}
	data->ray_dist = sqrtf((powf(x_d, 2)) +
				powf((y_d), 2)) * data->m_cell_size;
	printf("no %d has a distance of %f pixels\n", j++, data->ray_dist);
}*/

static	int hit_wall(t_data *data, double x_d, double y_d, int i)
{
	if ((data->map[(int)((data->player.y + y_d *
		data->m_cell_size - i - data->m_start_y)/
		data->m_cell_size)][(int)((data->player.x + x_d *
		data->m_cell_size - i)/data->m_cell_size)]) == '1')
	{
	printf("wall FOUND in map@ x: %d y: %d ---- x: %f y: %f \n", (int)((data->player.x + x_d * data->m_cell_size - i)/data->m_cell_size), (int)((data->player.y + y_d * data->m_cell_size - i - data->m_start_y)/
		data->m_cell_size), x_d, y_d);
//		if (x_d > 0)
//		{
//			draw_ray_xplus(data, x_d, y_d);
//			return (0);
//		}
		draw_ray(data, x_d, y_d);
			return (0);
	}
	printf("wall NOT in map@ x: %d y: %d ---- x: %f y: %f inc x_di: %f y_di %f\n", (int)((data->player.x + x_d * data->m_cell_size - i)/data->m_cell_size), (int)((data->player.y + y_d * data->m_cell_size - i - data->m_start_y)/
		data->m_cell_size), x_d, y_d, data->ray.x_di, data->ray.y_di);
//	printf("no hit x_d %f, y_d %f x_d/y_d %f\n", x_d, y_d, x_d / y_d);
	return (1);
}

static void	cast_one_ray(t_data *data, double x_d, double y_d)
{
	int i;

	i = 1;
	while (i < data->map_w && i < data->map_h)//TODO think,
	{
			if (i == 1 && x_d == 0 && y_d == 0 && !hit_wall(data, 0.1, 0.1, 2))//1 can be rounded/unvisible
				return ;
			else if (data->ray.x_di == -1)//vertical linecross
			{
				if ((int)(y_d + data->ray.y_di) == (int)y_d)//is the next int
				{
					if ((int)(x_d + data->ray.x_di) != (int)x_d)//is the next int
						x_d = (int)(x_d + data->ray.x_di);
					else
						x_d += data->ray.x_di;
					y_d = x_d / tan(data->ray.angle);
					if (!hit_wall(data, x_d, y_d, 1))
							return ;
				}
				else
				{	
					if ((int)(y_d + data->ray.y_di) != (int)y_d)//is the next int
						y_d = (int)(y_d + data->ray.y_di);
					else
						y_d += data->ray.y_di;
					x_d = y_d * tan(data->ray.angle);
					if (!hit_wall(data, x_d, y_d, 1))
						return ;
				}
				
			}
			else //horisontal linecross
			{	
				if ((int)(x_d + data->ray.x_di) == (int)x_d)//is the next int
				{
				if ((int)(y_d + data->ray.y_di) != (int)y_d)//is the next int
					y_d = (int)(y_d + data->ray.y_di);
				else
					y_d += data->ray.y_di;
				x_d = y_d * tan(data->ray.angle);
				if (!hit_wall(data, x_d, y_d, 1))
						return ;
				}
				else
				{
				if ((int)(x_d + data->ray.x_di) != (int)x_d)//is the next int
					x_d = (int)(x_d + data->ray.x_di);
				else
					x_d += data->ray.x_di;
				y_d = x_d / tan(data->ray.angle);
				if (!hit_wall(data, x_d, y_d, 1))
						return ;
				}	
			}

			i++;
		}
}

/*static void	cast_two_ray(t_data *data, double x_d, double y_d)
{
	int i;

	i = 1;
	while (i < data->map_w && data->map_h)//TODO think,
	{
			if (x_d == 0 && y_d == 0 && !hit_wall(data, 0.1, 0.1, 2))//1 can be rounded/unvisible
					return ;
			else if ((int)(data->ray.x_di) != (int)x_d)//vetical linecross
			{
					x_d = (int)((x_d) + data->ray.x_di);
					y_d = - x_d / tan(data->ray.angle);
					if (!hit_wall(data, x_d, y_d, 1))
						return ;
			}
			else//horisontal linecorss
			{	
				if ((float)(y_d) != 0)
					y_d = (int)y_d;
				y_d -= 1;
				x_d = - y_d / ( data->ray.slope);
				if (!hit_wall(data, x_d, y_d, 1))
					return ;
			}
			i++;
		}
}*/

/*
@glance		computes the axis incrementations for one ray
*/

static void	init_ray_inc(t_data *data)
{
	double	x;
	double	y;

	x = -1;
	data->ray.y_di = x / tan(data->ray.angle);
	y = -1;
	data->ray.x_di = y * tan(data->ray.angle);
	if (fabs(data->ray.x_di) > fabs(data->ray.y_di))
		data->ray.x_di = -1;
	else		
		data->ray.y_di = -1;
	data->ray.slope = data->ray.y_di / data->ray.x_di;
	return ;
}

/*
@glance		a wall hit is actually a horisontal or vertical line crossing
			where corresponding map[x][y] has '1' value. 
 *not using vectors since the ray degree does not change, one ray until wall
 hit.
 *
 * spawning pos 270, H_FOW 30, first ray 240deg.
 * ray crossing with the next y axis is x = 1 (ie one cell on 2Dmap). this
 * is tan30
 *
@tan		tan(alpha) = x_d / y_d
@cast_one		loop per ray, looks for vertical or horizontal line crossigs
 * */

void	cast_rays(t_data *data)
{
	double	x_d;
	double	y_d;

	x_d = 0;
	y_d = 0;
	data->ray.angle = H_FOV * PI/180;
	while (data->ray.angle >= - H_FOV * PI/180)
	{
		init_ray_inc(data);
		cast_one_ray(data, x_d, y_d);
		data->ray.angle -= PI/180;
	}
	/*x_d = 0;
	y_d = 0;
	data->ray.angle = 0.001;
	data->ray.y_di = -1;	
	while (data->ray.angle <= H_FOV * PI/180)
	{
		data->ray.x_di = - data->ray.y_di * tan(data->ray.angle);//x is pos
		data->ray.slope = - data->ray.y_di / data->ray.x_di;
		printf("slope %f, x: %f, y: %f\n", data->ray.slope, data->ray.x_di, data->ray.y_di);
		cast_two_ray(data, x_d, y_d);
		data->ray.angle += PI/180;
	}
*/
}
