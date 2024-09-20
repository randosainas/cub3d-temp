/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:31:04 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/20 12:47:53 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
/*
@glance			scale the screen width, comp ray direction and ray vector.
@scale & norm 	scale_x=2* this enables to scale the screen width
				ie [0,1000] to [-1,1], multiplication by one would 
				scale it to [0,1]. Screen plane extends to the negative
				side form players position.
@->ray[x,y]		a ray vector and its x and y axis deltas/projections
				and represent a direction a ray is casted. 
				So the rays range from [-1, -0.66] to [1, 0.66].
@->player_x		player directional vector and its components, vector from
				player position to camera plane vector and perpendicular
				to camera plane vector.
@ray.delta_x	scaled distance a ray must travel (projected on x-axis) to 
				cross the next vertcal line.
@1e-8			a very small number to make a reliable double number 
				comparison to 0. Needed to avoid division by 0.
*/

void	scale_pos_dir(t_data *data, int i)
{
	double	scale_x;

	scale_x = 2 * i / (double)WIN_WIDTH - 1; //x-coordinate in camera space
	data->ray.x = data->ray.player_x + data->ray.plane_x * scale_x;
	data->ray.y = data->ray.player_y + data->ray.plane_y * scale_x;
//	printf("scale_x %f data->ray.x/Y %f / %f\n", scale_x, data->ray.x, data->ray.y);
	data->ray.map_x = data->player.x_i;
	data->ray.map_y = data->player.y_i;
//	printf("player's box: %d / %d\n", data->ray.map_x, data->ray.map_y);
  //length of ray from current position to next x or y-side
  //length of ray from one x or y-side to next x or y-side 
	if (fabs(data->ray.x) < 1e-8)
		data->ray.x = 314748366;
	else
		data->ray.delta_x = fabs(1 / data->ray.x);
	if (fabs(data->ray.y) < 1e-8)
		data->ray.y = 3147483366;
	else
	data->ray.delta_y = fabs(1 / data->ray.y);
//	printf("ray length x %f y %f\n", data->ray.delta_x, data->ray.delta_y);
}

/*
@glance		compute one ray side step, who much the ray can move till the
			first horisontal or vertical line crossing.
			which direction to step 1 or -1.
*/

void	comp_ray_side_step(t_data *data)
{
	if (data->ray.x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_x = (data->player.x_i - data->ray.map_x) * data->ray.delta_x;
	}
	else// ports assiging that value.  
	{
		data->ray.step_x = 1;
		data->ray.side_x = (data->ray.map_x + 1.0 - data->player.x_i) * data->ray.delta_x;
	}
	if (data->ray.y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_y = (data->player.y_i - data->ray.map_y) * data->ray.delta_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_y = (data->ray.map_y + 1.0 - data->player.y_i) * data->ray.delta_y;
	}
//	printf("side.x sideDistx%f y %f\n", data->ray.side_x, data->ray.side_y);
//	printf("sideDist x %f y %f\n", data->ray.side_x, data->ray.side_y);
}

/*
@glance		DigitalDifferencialAnalyser is moving along the ray line, with
			steps that have deltas on x and y axis. efficient comared to
			moving by line equation with step as each point on the line. 
@side=0		ray hit the vertical line EW wall, 1 ray hit the hor grid line
			ie NS wall.
@side_x		cummulative distance on each axis a ray has travelled while hit. 
*/

void	move_along_ray_dda(t_data *data)
{
	data->ray.hit = 0; 
//	printf("()(map x %d, map_y %d\n", data->ray.map_x, data->ray.map_y);
	while (data->ray.hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (data->ray.side_x < data->ray.side_y)//which ever smaller comes first not to
			// miss any line crossings.
		{
			data->ray.side_x += data->ray.delta_x;
			data->ray.map_x += data->ray.step_x;//data->ray.map_x is the current box the ray is in
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_y += data->ray.delta_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		  //Check if ray has hit a wall	
		if (data->map[data->ray.map_x][data->ray.map_y] == '1')
		{
			data->ray.hit = 1;
//			printf("map x %d, map_y %d\n", data->ray.map_x, data->ray.map_y);
//			printf("player pos x  %d, pos y %d\n", data->player.x_i, data->player.y_i);
//			printf("ray delta x  %f, ray delta y %f\n", data->ray.delta_x,
//				   	data->ray.delta_y);
//			printf("sideDist x %f y %f\n", data->ray.side_x, data->ray.side_y);
//			printf("WALL @ data->ray.map_x %d data->ray.map_y %d\n", data->ray.map_x, data->ray.map_y);
//		printf("map pos: %d, data->ray.map_x %d data->ray.map_y %d \n", data->map[data->ray.map_x][data->ray.map_y], data->ray.map_x, data->ray.map_y);
		}
//		if (data->ray.hit == 0)
//		{
//			printf("sideDist x %f y %f\n", data->ray.side_x, data->ray.side_y);
//			printf("not found @ data->ray.map_x %d data->ray.map_y %d\n", data->ray.map_x, data->ray.map_y);
	}
}
