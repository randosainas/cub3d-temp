/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:16:23 by lpetit            #+#    #+#             */
/*   Updated: 2024/10/02 19:40:14 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int check_rgb(char *line)
{
    int i;

    i = 0;
    if (line[0] == '\0' || line[0] == '\n')
        return (1);
    while (line[i] != 32 && line[i] != ',' && line[i] != '\n')
    {
        if (!ft_isdigit(line[i]))
            return (1);
        i++;
    }
    if (ft_atoi(line) > 255 || ft_atoi(line) < 0)
        return (1);
    return (0);
}

int check_content(char *line, t_data *data)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 32)
        {
            if ((line[i] == 'N' || line[i] == 'S' ||
						line[i] == 'E' || line[i] == 'W')
                && data->player.player_found == 0)
				data->player.player_found = 1;
            else if ((line[i] != '\n' && line[i] != '\0') || (i == 0 && line[i] == '\n'))
                return (1);
        }
        i++;
    }
    return (0);
}

void    map_content(char *line, t_data * data)
{
    char    *buffer;

    buffer = ft_strdup("");
    while (line)
    {
        if (!check_content(line, data))
            buffer = ft_strjoin_f(buffer, line);
        else
        {
            free(line);
            free(buffer);
            err_msg("Invalid map configuration", data, 1);
        }
        line = get_next_line(data->fd);
    }
    data->map = ft_split(buffer, '\n');
    free(buffer);
}

void    parse_element(char *line, t_data *data)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        data->no_path = set_path(line, data);
    else if (ft_strncmp(line, "SO", 2) == 0)
        data->so_path = set_path(line, data);
    else if (ft_strncmp(line, "WE", 2) == 0)
        data->we_path = set_path(line, data);
    else if (ft_strncmp(line, "EA", 2) == 0)
        data->ea_path = set_path(line, data);
    else if (ft_strncmp(line, "F ", 2) == 0)
        set_color_floor(line, data);
    else if (ft_strncmp(line, "C ", 2) == 0)
        set_color_ceiling(line, data);
    else
    {
        free(line);
        err_msg("Invalid element configuration", data, 1);
    }
    data->map_start++;
}
