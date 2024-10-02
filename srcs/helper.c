/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:51:19 by lpetit            #+#    #+#             */
/*   Updated: 2024/10/02 11:43:06 by rsainas          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

void	get_map_size(t_data *data)
{
	int	i;
	size_t size;

	i = 0;
	if (data->map)
		size = ft_strlen(data->map[i]);
	while (data->map && data->map[i])
	{
		if (size < ft_strlen(data->map[i]))
			size = ft_strlen(data->map[i]);
		i++;
	}
	data->map_copy.map_size = i;
	data->map_copy.line_size = size;
}

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

void	free_all_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	free_texture_path(t_data *data)
{
	if (data->no_path != NULL)
		free(data->no_path);
	if (data->so_path != NULL)
		free(data->so_path);
	if (data->we_path != NULL)
		free(data->we_path);
	if (data->ea_path != NULL)
		free(data->ea_path);
}

void	err_msg(char *msg, t_data *data, int need_free)
{
	printf("%s\n%s\n", "Error", msg);
	if (need_free == 0)
		exit(1);
	free_texture_path(data);
	if (data->map)
		free_all_tab(data->map);
	if (data->fd != -1)
		close(data->fd);
	exit(1);
}
