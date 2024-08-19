/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:09:19 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/15 08:34:16 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

char    *skip_empty(int fd, t_data *data)
{
    char    *line;

    line = get_next_line(fd);
    if (!line)
        return (NULL);
    while (line && ft_strncmp(line, "\n", 1) == 0)
    {
        data->map_start++;
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

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

int check_rgb(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i] != 32 && line[i] != ',' && line[i] != '\n')
    {
        if (!ft_isdigit(line[i]) || count == 4)
            return (1);
        count++;
        i++;
    }
    return (0);
}

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
            exit(1);
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
            exit(1);
        while (tmp && ft_isdigit(*tmp))
            tmp++;
        i++;
    }
}

char    *set_path(char *line)
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
        exit(1);
    return (dup);
}

void    parse_element(char *line, t_data *data)
{
    if (ft_strncmp(line, "NO", 2) == 0)//TODO will give a false positive in case "NOX"
        data->no_path = set_path(line);
    else if (ft_strncmp(line, "SO", 2) == 0)
        data->so_path = set_path(line);
    else if (ft_strncmp(line, "WE", 2) == 0)
        data->we_path = set_path(line);
    else if (ft_strncmp(line, "EA", 2) == 0)
        data->ea_path = set_path(line);
    else if (ft_strncmp(line, "F ", 2) == 0)
        set_color_floor(line, data);
    else if (ft_strncmp(line, "C ", 2) == 0)
        set_color_ceiling(line, data);
    else
        exit(1);
    data->map_start++;
}

char    *init_element(int fd, t_data *data)
{
    char    *line;
    int     i;

    i = 0;
    data->no_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;
    data->ea_path = NULL;
    data->map_start = 0;
    while (i < 6)//TODO element integrity check, in case one path is missing
    {
        line = skip_empty(fd, data);
        parse_element(line, data);//TODO segfaults in case gnl returns NULL to skip_empty;
        if (line)
            free(line);
        i++;
    }
    return (skip_empty(fd, data));
}

int check_content(char *line, t_data *data)
{
    int i;

    i = 0;
    data->player.player_found = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 32)
        {
            if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
                && data->player.player_found == 0)
            {
                data->player.face = line[i];
                data->player.player_found = 1;
                //printf("i in first if = %d\n", i);
			}
			else if (line[i] != '\n' && line[i] != '\0')
            {
                //printf("line =%s\n", line);
                //printf("line[i]= %c\n", line[i]);
                //printf("i in 2nd if = %d\n", i);
                //printf("is player found ? =%d\n", data->player.player_found);
                return (1);
            }
        }
        //printf("is player found ? =%d\n", data->player.player_found);
        //printf("line[i]= %c\n", line[i]);
        i++;
    }
    return (0);
}

/*int get_map_size(char *path, t_data *data)
{
    char    *line;
    int fd;
    int line_count;

    line_count = 0;
    fd = open(path, O_RDONLY);
    line = init_element(fd, data);
    while (line)
    {
        line_count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    printf("line_count =%d\n", line_count);
    return (line_count);
}*/

/*void    map_init(char  *path, t_data *data)
{
    char    *line;
    int     fd;
    int     i;
    int     size;
    // false read to get map size
    // malloc the right map size
    i = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        exit(1);
    size = get_map_size(path, data);
    //data->map = malloc(sizeof(char *) * get_map_size(path, data) + 1);
    data->map = malloc(sizeof(char *) * size + 1);
    data->map[size] = NULL;
    //printf("%s\n", "here2");
    if (!data->map)
        exit(1);
    line = skip_to_map(fd, data);
    //printf("%s\n", "here3");
    while (line)
    {
        //printf("%s\n", "here4");
        // read line by line and store in the data.map after checking each line
        if (!check_content(line, data))
        {
            //line[ft_strlen(line) - 1] = '\0';
            data->map[i] = line;
            i++;
        }
        else
        {
            //printf("%s\n", "check_content return 1");
            free(line);
            exit(1);
        }
        line = get_next_line(fd);
    }
    close(fd);
    //printf("%s\n", "here5");
    // malloc bigger map, fill it with special character
    // iterate in false map in both direction and check for special character each time 0 is encountered
}*/

void    map_init(char  *path, t_data *data)
{
    char    *line;
    char    *buffer;
    int     fd;
    int     i;

    i = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)//TODO file extention check .cub
        exit(1);
    line = init_element(fd, data);//TODO skip_empty might return NULL from gnl
    buffer = ft_strdup("");//TODO malloc fail in strdup
    while (line)
    {
        if (!check_content(line, data))
        {
            buffer = ft_strjoin_f(buffer, line);//TODO malloc fail
            i++;
        }
        else
        {
            free(line);
            exit(1);
        }
        line = get_next_line(fd);
    }
    data->map = ft_split(buffer, '\n');//TODO malloc fail
    free(buffer);
    close(fd);
}
