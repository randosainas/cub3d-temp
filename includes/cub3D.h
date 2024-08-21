/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:52:03 by lpetit            #+#    #+#             */
/*   Updated: 2024/08/21 11:18:10 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
# include "../minilibx-linux/mlx.h"
//# include <X11/X.h>//keyboard key values


# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define WHITE		(0xFFFFFF)
# define BLACK		(0x000000)
# define GREY		(0x808080)
# define RED		(0xFF0000)
# define BLUE		(0x0000FF)
# define GREEN		(0x00FF00)
# define ORANGE		(0xFFA500)

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

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
<<<<<<< HEAD
	int		map_w;
	int		map_h;
	int		m_cell_size;
	char	*name;
	void	*mlx;
	void	*win;
	t_img	img;
=======
    int     closed;
    int     fd;
>>>>>>> map
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

// GRAPHICS
void		init_graphics(t_data *data);
void		ft_exit(t_data *data);
int			close_window(t_data *data);
int			render(t_data *data);
void		pixel_put(t_img *img, int x, int y, int color);
void		map_size(t_data *data);
void		draw_map(t_data *data);
#endif
