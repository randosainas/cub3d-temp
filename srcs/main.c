/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:49:45 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/22 09:50:00 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2)
        exit(1);
    if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		err_msg("Invalid map extension", &data, 0);
	map_init(argv[1], &data);
    //printf("no_path:%s\n", data.no_path);
    //printf("so_path:%s\n", data.so_path);
    //printf("we_path:%s\n", data.we_path);
    //printf("ea_path:%s\n", data.ea_path);
    //printf("floor:%d %d %d\n", data.floor.r, data.floor.g, data.floor.b);
    //printf("ceiling:%d %d %d\n\n", data.ceiling.r, data.ceiling.g, data.ceiling.b);
    //int i = 0;
    //while (data.map[i])
    //{
    //    printf("%s\n", data.map[i]);
    //    i++;
    //}
    if (check_if_closed(&data) == 1)
		err_msg("Map is not closed", &data, 1);
	data.name = argv[1];
	init_graphics(&data);	
	map_size(&data);
	render(&data);
	mlx_loop(data.mlx);
    free_all_tab(data.map);
    free_texture_path(&data);
    return (0);
}
