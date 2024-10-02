/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:15:01 by rsainas           #+#    #+#             */
/*   Updated: 2024/10/02 14:38:58 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
@glance		put texture pixels to allocated textures array
*/

static void	copy_to_array(t_data *data, int tex_num, int *img_data)
{
	int	x;
	int	y;

	y = -1;
	while (y++, y < TEXTURE_H)
	{
		x = -1;
		while (x++, x < TEXTURE_W)
			data->textures[tex_num][y * TEXTURE_W + x] = img_data
			[y * TEXTURE_W + x];
	}
}

/*
@glance		let mlx convert xpm to an array, get address of this array
*/

static void	assign_texture(t_data *data, int tex_num, char *path)
{
	int		width;
	int		height;
	void	*img;
	int		*img_data;
	int		size_line;

	img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!img || width != TEXTURE_W || height != TEXTURE_H)
	{
		printf("Loading failed to a texture: %s\n", path);
		while (tex_num >= 0)
		{
			free(data->textures[tex_num]);
			tex_num--;
		}
		exit(EXIT_FAILURE);
	}
	img_data = (int *)mlx_get_data_addr(img, &data->img.bits_per_pixel,
			&size_line, &data->img.endian);
	copy_to_array(data, tex_num, img_data);
	mlx_destroy_image(data->mlx, img);
}

/*
@glance		allocate an int pointer array of 4 pointers, call assign
*/

void	init_textures(t_data *data)
{
	int	i;

	i = -1;
	while (i++, i < 4)
	{
		data->textures[i] = (int *)malloc
			(sizeof(int) * (TEXTURE_W * TEXTURE_H));
		if (!data->textures[i])
		{
			printf("Memory allocation failed for a texture %d\n", i);
			while (i >= 0)
			{
				i--;
				free(data->textures[i]);
			}
			exit(EXIT_FAILURE);
		}
	}
	assign_texture(data, 0, data->no_path);
	assign_texture(data, 1, data->ea_path);
	assign_texture(data, 2, data->so_path);
	assign_texture(data, 3, data->we_path);
}

void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (i++, i < 4)
		free(data->textures[i]);
}
