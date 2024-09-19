/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:37:59 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/19 20:49:43 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	cast_walls(t_data *data)
{
	double	perpWallDist;
    int drawStart;
    int drawEnd;
    /*double wallX;
	int texX;
    int texY;	
	double step;
    int texNum;
	double texPos;*/
	int color;
	int y;
/*

*/
    
	int i;
	i = 0;
	while (i < WIN_WIDTH - 1)
    {
		scale_pos_dir(data, i);
		comp_ray_side_step(data);
		move_along_ray_dda(data);

		/*Calculate distance of perpendicular ray (
			Euclidean distance would give fisheye effect!)*/
/*
@glance				comp distance from player to the hit wall. 
ray.side_x or y		has an additioal incremental distance prior the hit, that 
					needs to be substracted to get the distance to the hit wall
@line_h				line height to be drawn on the screen is inversly
					releated to window height. The closer the wall to player
					the higher the line on the screen.
*/
		if (data->ray.side == 0)
			perpWallDist = (data->ray.side_x - data->ray.delta_x);
		else
			perpWallDist = (data->ray.side_y - data->ray.delta_y);
    	//Calculate height of line to draw on screen
		data->ray.line_h = (int)(WIN_HEIGHT / perpWallDist);
//		printf("ray.side_x %f, ray.side_y %f, ray.delta_x %f, ray.delta_y %f, perWallDist %f, lineH %d\n",
//		data->ray.side_x, data->ray.side_y, data->ray.delta_x, data->ray.delta_y, perpWallDist, data->ray.line_h);
	 	//calculate lowest and highest pixel to fill in current stripe
		drawStart = -data->ray.line_h / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = data->ray.line_h / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;
    	  //texturing calculations
/*			texNum = ft_atoi(&(data->map[data->ray.map_x][data->ray.map_y])) - 1; //1 subtracted from 
				//it so that texture 0 can be used!
   			 	  //calculate value of wallX
     			 //where exactly the wall was hit 
		if (data->ray.side == 0) 
			wallX = data->player.y + perpWallDist * data->ray.y;
		else
			wallX = data->player.x + perpWallDist * data->ray.x;
				 //	wallX -= floor((wallX));
			      //x coordinate on the texture
		texX = (int)wallX * (double)TEXTURE_W;
		if ((data->ray.side == 0 && data->ray.x > 0) || (data->ray.side == 1 && data->ray.y < 0))
		{
			texX = TEXTURE_W - texX -1;
		}
//	if (data->ray.side == 1 && data->ray.y < 0)
//		texX = TEXTURE_W - texX - 1;

      // How much to increase the texture coordinate per screen pixel
	step = 1.0 * TEXTURE_H / data->ray.line_h;
      // Starting texture coordinate
	texPos = (drawStart - WIN_HEIGHT / 2 + data->ray.line_h / 2) * step;
*/
//allocate buffer int array of arrays
//	int i;

//	i = 0;
	/*while (i < WIN_WIDHT, i++)
	{
	  data->buffer[i] = ft_calloc(WIN_HEIGHT, sizeof(int));
	  if (!data->buffer[i])
		 exit();//TODO proper free
	}	*/
	y = drawStart;
	while (y < drawEnd)
     {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//		texY = (int)texPos;// & (TEXTURE_H - 1);
//      texPos += step;
		color = GREY;// + TEXTURE_W + texY + texX;
 //       int color = texture[texNum][TEXTURE_W * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if (data->ray.side == 1)
			color = (color >> 1) & 8355711;
		pixel_put(&data->img, i, y, color);
		y++;
      }
//	printf("---------------------------Column on screen %d drawStart %d drawEnd %d\n", i, drawStart, drawEnd);
	i++;
	}
//	printf("End of loop %d\n", x);
}
