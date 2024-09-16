/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:37:59 by rsainas           #+#    #+#             */
/*   Updated: 2024/09/16 09:27:24 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

//WALL CASTING

void	cast_walls()
{
	double	dirX;
	double dirY;
	double	planeX;
	double planeY;


	dirX = -1;//TODO figure out if this is facing west?
	dirY = 0;
	planeX = 0;
	planeY = 0.66;
    
	for(int x = 0; x < WIN_WIDTH; x++)
    {
      //calculate ray position and direction
	double	cameraX;
	
	cameraX = 0;  
	cameraX = 2 * x / double(WIN_WIDTH) - 1; //x-coordinate in camera space

	double	rayDirX;
 	double	rayDirX;

	rayDirX = 0;
	rayDirY = 0;
	  
	rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;

      //which box of the map we're in
	int	mapX;
	int	mapY;
	
	mapX = int(data->player.x);
	mapY = int(data->player.y);

      //length of ray from current position to next x or y-side
	double	sideDistX;
 	double	sideDistY;

      //length of ray from one x or y-side to next x or y-side
	double	detaDistX;
	double	deltaDistY;
	  
	deltaDistX = fabs(1 / rayDirX);
	deltaDistY = abs(1 / rayDirY);
	double	perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
	int	stepX;
	int	stepY;

	int hit = 0; //was there a wall hit?
 	int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (data->player.x - mapX) * deltaDistX;
      }
      else
    ports assiging that value.  {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (data->player.y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
      }
	}
    //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (ft_atoi(data->map[mapX][mapY]) > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;
      //texturing calculations
      int texNum = ft_atoi(data->map[mapX][mapY]) - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = data->player.y + perpWallDist * rayDirY;
      else           wallX = data->payer.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
//allocate buffer int array of arrays
	int i;

	i = 0;
	while (i < WIN_WIDHT, i++)
	{
	  data->buffer[i] = ft_calloc(WIN_HEIGHT, sizeof(int));
	  if (!data->buffer[i])
		 exit();//TODO proper free
	}	
	
	for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = GREY;//texture[texNum][texWidth * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
}
