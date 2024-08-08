/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:49:45 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/08 13:25:05 by lpetit           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2)
        exit(1);
    map_init(argv[1], &data);
    //printf("%s\n", "here5");
    printf("no_path:%s\n", data.no_path);
    printf("so_path:%s\n", data.so_path);
    printf("we_path:%s\n", data.we_path);
    printf("ea_path:%s\n", data.ea_path);
    printf("floor:%d %d %d\n", data.floor.r, data.floor.g, data.floor.b);
    printf("ceiling:%d %d %d\n\n", data.ceiling.r, data.ceiling.g, data.ceiling.b);
    int i = 0;
    while (data.map[i])
    {
        printf("%s\n", data.map[i]);
        i++;
    }
    free_all_tab(data.map);
    free_texture_path(&data);
    return (0);
}