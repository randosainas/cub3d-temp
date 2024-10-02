/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:31:04 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/02 16:54:36 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
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

	scale_x = 2 * i / (double)WIN_WIDTH - 1;
	data->ray.x = data->ray.player_x + data->ray.plane_x * scale_x;
	data->ray.y = data->ray.player_y + data->ray.plane_y * scale_x;
	data->ray.map_x = data->player.x_i;
	data->ray.map_y = data->player.y_i;
	if (fabs(data->ray.x) < 1e-8)
		data->ray.x = 314748366;
	else
		data->ray.delta_x = fabs(1 / data->ray.x);
	if (fabs(data->ray.y) < 1e-8)
		data->ray.y = 3147483366;
	else
		data->ray.delta_y = fabs(1 / data->ray.y);
}

/*
@glance		compute one ray side step, who much the ray can move till the
			first horisontal or vertical line crossing.
			which direction to step 1 or -1. This is different sixe from 
			the next constant ray projections till crossing map lines 
			ie delta_x and delta_y.
*/

void	comp_ray_side_step(t_data *data)
{
	if (data->ray.x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_x = (data->player.x_i - data->ray.map_x)
			* data->ray.delta_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_x = (data->ray.map_x + 1.0 - data->player.x_i)
			* data->ray.delta_x;
	}
	if (data->ray.y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_y = (data->player.y_i - data->ray.map_y)
			* data->ray.delta_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_y = (data->ray.map_y + 1.0 - data->player.y_i)
			* data->ray.delta_y;
	}
}

/*
@glance		DigitalDifferencialAnalyser is moving along the ray line, with
			steps that have deltas on x and y axis. efficient comared to
			moving by line equation with step as each point on the line.
@if			which ever projection is smaller is checked first not to miss
			ray crossing ver or hor map lines.
@side=0		ray hit the vertical line EW wall, 1 ray hit the hor grid line
			ie NS wall.
@side_x		cummulative distance on each axis a ray has travelled while hit.
@map_x		move to the next map square
@2nd if		have we hid a wall
*/

void	move_along_ray_dda(t_data *data)
{
	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.side_x < data->ray.side_y)
		{
			data->ray.side_x += data->ray.delta_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_y += data->ray.delta_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_x][data->ray.map_y] == '1')
			data->ray.hit = 1;
	}
}
