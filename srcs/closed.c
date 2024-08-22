/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:29:46 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/22 09:51:43 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

void    find_player(char **map, t_pos *player)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (map[x])
    {
        while (map[x][y])
        {
            if (map[x][y] == 'N' || map[x][y] == 'S'
                || map[x][y] == 'E' || map[x][y] == 'W')
            {
                player->x = x;
                player->y = y;
                break ;
            }
            y++;
        }
        y = 0;
        x++;
    }
}

char    **copy_alloc(t_data *data)
{
    char    **copy;
    int     i;

    i = 0;
    get_map_size(data);
    copy = malloc((data->map_copy.map_size + 3) * sizeof(char *));
    if (!copy)
        return (NULL);
    while (i < data->map_copy.map_size + 2)
    {
        copy[i] = malloc(data->map_copy.line_size + 3);
        if (!copy[i])
        {
            free_all_tab(copy);
            return (NULL);
        }
        ft_memset((void *)copy[i], 'X', data->map_copy.line_size + 2);
        copy[i][data->map_copy.line_size + 2] = '\0';
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

void    map_copy(t_data *data, char **copy)
{
    int i;
    int c;

    i = 0;
    c = 0;
    while (data->map[i] != NULL)
    {
        while (data->map[i][c] != '\0')
        {
            if (data->map[i][c] != ' ')
                copy[i + 1][c + 1] = data->map[i][c];
            c++;
        }
        c = 0;
        i++;
    }
}

int is_closed(t_data *data, char **copy, int line, int col)
{
    if (copy[line][col] == 'X')
        data->closed = 1;
    copy[line][col] = '1';
    if (data->closed == 0 && copy[line - 1][col] != '1')
        is_closed(data, copy, line - 1, col);
    if (data->closed == 0 && copy[line + 1][col] != '1')
        is_closed(data, copy, line + 1, col);
    if (data->closed == 0 && copy[line][col - 1] != '1')
        is_closed(data, copy, line, col - 1);
    if (data->closed == 0 && copy[line][col + 1] != '1')
        is_closed(data, copy, line, col + 1);
    if (data->closed == 1)
        return (1);
    return (0);
}

int check_if_closed(t_data *data)
{
    char    **copy;
    t_pos   player;

    copy = copy_alloc(data);
    if (!copy)
        err_msg("malloc error", data, 1);
    map_copy(data, copy);
    data->closed = 0;
    find_player(copy, &player);
    if (is_closed(data, copy, player.x, player.y) == 1)
    {
        free_all_tab(copy);
        return (1);
    }
    free_all_tab(copy);
    return (0);
}
