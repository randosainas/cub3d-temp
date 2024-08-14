/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:52:03 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/14 17:49:06 by lpetit           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

typedef struct s_copy
{
    int map_size;
    int line_size;
}   t_copy;

typedef struct s_pos
{
    size_t  x;
    size_t  y;
    char    face;
    int     player_found;
}   t_pos;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_data
{
    t_pos   player;
    char    **map;
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    t_color floor;
    t_color ceiling;
    t_copy  map_copy;
    int     map_start;
    int     closed;
    int     fd;
}   t_data;

char	**ft_split(char const *s, char c);
char    *init_element(t_data *data);
//char    *skip_to_map(int fd, t_data *data);
char    *skip_empty(int fd, t_data *data);
char    *set_path(char *line, t_data *data);

void    get_map_size(t_data *data);
int check_rgb(char *line);
int check_content(char *line, t_data *data);
int check_if_closed(t_data *data);

void    map_init(char  *path, t_data *data);
void    map_content(char *line, t_data * data);
void    parse_element(char *line, t_data *data);
void    set_color_ceiling(char *line, t_data *data);
void    set_color_floor(char *line, t_data *data);


void	free_all_tab(char **tab);
void	free_texture_path(t_data *data);
void	err_msg(char *msg, t_data *data, int need_free);

#endif