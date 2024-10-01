/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:52:03 by lpetit            #+#    #+#             */
/*   Updated: 2024/10/01 20:32:55 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "math.h"
# include <X11/X.h>//keyboard key values

//Main settings
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define H_FOV 90
# define PI 3.1415926
# define TEXTURE_H 64
# define TEXTURE_W 64

//Colors
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
    size_t  x;//for 2D minimap
    size_t  y;
	double		x_i;//current pos of player
	double		y_i;
    int		face;
    int		player_found;
}   t_pos;

//each ray has a slope and the first line crossing point and its projections
//x_d and y_d, angle in radian
typedef struct	s_ray
{
	double	player_x;//directional vector components
	double	player_y;
	int		map_x;
	int		map_y;
	int		hit;
	double	side_x;
 	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		side;
	double	x;
 	double	y;
	int		line_h;
	int		line_start;
	int		line_end;	
	double	p_wall_dist;
	double	plane_x;
	double	plane_y;
	double	wallX;//nameing
	int		texX;
	int		texY;	
	double	step;
    int		tex_nr;
	double	texPos;
	
//old stuff
	double	angle;
	double	slope;
	double	x_di;
	double	y_di;
}	t_ray;

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
	int		*textures[4];
    t_color floor;
    t_color ceiling;
    t_copy  map_copy;
    int     map_start;
	int		map_w;
	int		map_h;
	int		m_start_y;//2D map y position
	int		m_cell_size;
	t_ray	ray;
	double	ray_dist;
	char	*name;
	void	*mlx;
	void	*win;
	t_img	img;
	double	step;//step size, how much the player moves on one keypress
	double	rot;//rotation left and right
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

// GRAPHICS
void		init_graphics(t_data *data);
void		ft_exit(t_data *data);
int			close_window(t_data *data);
void		draw_ceiling_floor(t_data *data);
int			render(t_data *data);
void		pixel_put(t_img *img, int x, int y, int color);
void		map_size(t_data *data);
void		draw_map(t_data *data);
//vector approach
void		cast_rays(t_data *data);
void		scale_pos_dir(t_data *data, int i);
void		comp_ray_side_step(t_data *data);
void		move_along_ray_dda(t_data *data);
int			key_stroke(int key, t_data *data);
void		init_player_pos(t_data *data);
void		init_textures(t_data *data);
#endif
