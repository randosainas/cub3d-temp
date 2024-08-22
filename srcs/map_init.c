/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:09:19 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/21 11:36:53 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

/*char    *skip_to_map(int fd, t_data *data)
{
    char    *line;
    int     i;

    i = 0;
    line = get_next_line(fd);
    if (!line)
        return (NULL);
    while (line && i < data->map_start)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}*/

void    set_color_ceiling(char *line, t_data *data)
{
    int i;
    char    *tmp;

    i = 0;
    tmp = line;
    tmp++;
    while (i < 3)
    {
        while (*tmp == 32 || *tmp == ',')
            tmp++;
        if (i == 0 && !check_rgb(tmp))
            data->ceiling.r = ft_atoi(tmp);
        else if (i == 1 && !check_rgb(tmp))
            data->ceiling.g = ft_atoi(tmp);
        else if (i == 2 && !check_rgb(tmp))
            data->ceiling.b = ft_atoi(tmp);
        else
        {
            free(line);
            err_msg("Invalid RGB configuration", data, 1);
        }
        while (tmp && ft_isdigit(*tmp))
            tmp++;
        i++;
    }
}

void    set_color_floor(char *line, t_data *data)
{
    int i;
    char    *tmp;

    i = 0;
    tmp = line;
    tmp++;
    while (i < 3)
    {
        while (*tmp == 32 || *tmp == ',')
            tmp++;
        if (i == 0 && !check_rgb(tmp))
            data->floor.r = ft_atoi(tmp);
        else if (i == 1 && !check_rgb(tmp))
            data->floor.g = ft_atoi(tmp);
        else if (i == 2 && !check_rgb(tmp))
            data->floor.b = ft_atoi(tmp);
        else
        {
            free(line);
            err_msg("Invalid RGB configuration", data, 1);
        }
        while (tmp && ft_isdigit(*tmp))
            tmp++;
        i++;
    }
}

char    *set_path(char *line, t_data *data)
{
    char    *tmp;
    char    *dup;

    tmp = line;
    tmp++;
    tmp++;
    while (*tmp == 32)
        tmp++;
    tmp[ft_strlen(tmp) - 1] = '\0';
    dup = ft_strdup(tmp);
    if (!dup)
        err_msg("Could not allocate memory for the elements", data, 1);
    return (dup);
}

char    *init_element(t_data *data)
{
    char    *line;
    int     i;

    i = 0;
    data->no_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;
    data->ea_path = NULL;
    data->map = NULL;
    data->map_start = 0;
    data->player.player_found = 0;
    while (i < 6)//TODO element integrity check, in case one path is missing
    {
        line = skip_empty(data->fd, data);
        if (!line)
            return (NULL);
        parse_element(line, data);//TODO segfaults in case gnl returns NULL to skip_empty;
        if (line)
            free(line);
        i++;
    }
    return (skip_empty(data->fd, data));
}

void    map_init(char  *path, t_data *data)
{
    char    *line;

    data->fd = open(path, O_RDONLY);
    line = init_element(data);
    if (!line)
        err_msg("Invalid map configuration", data, 1);
    map_content(line, data);
    if (data->player.player_found == 0)
        err_msg("Invalid map configuration, no player found", data, 1);
    if (!data->map)
        err_msg("Could not allocate memory for the map", data, 1);
    close(data->fd);
}
