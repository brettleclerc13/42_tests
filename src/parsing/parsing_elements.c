/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:36:32 by brettlecler       #+#    #+#             */
/*   Updated: 2024/01/11 17:17:52 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	comma_count(char *colour_char)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (colour_char[++i])
		if (colour_char[i] == ',')
			comma++;
	return (comma);
}

static t_colours	*retrieve_colour_values(t_cub *cube, char *colour_char)
{
	char		**tmp;
	t_colours	*colour_combo;

	colour_combo = ft_calloc(1, sizeof(t_colours));
	colour_combo->r = 0;
	colour_combo->g = 0;
	colour_combo->b = 0;
	tmp = ft_split(colour_char, ',');
	if (ft_arraylen(tmp) != 3)
	{
		ft_arrayfree(tmp);
		ft_free_exit(8, cube);
	}
	colour_combo->r = ft_atoi(tmp[0]);
	colour_combo->g = ft_atoi(tmp[1]);
	colour_combo->b = ft_atoi(tmp[2]);
	if (colour_combo->r > 255 || colour_combo->g > 255 || colour_combo->b > 255)
	{
		ft_arrayfree(tmp);
		ft_free_exit(9, cube);
	}
	ft_arrayfree(tmp);
	return (colour_combo);
}

static void	check_colour_values(t_cub *cube)
{
	if (comma_count(cube->c) != 2 || comma_count(cube->f) != 2)
		ft_free_exit(8, cube);
	if (cube->c[0] == ',' || cube->f[0] == ',')
		ft_free_exit(8, cube);
	cube->c_colours = retrieve_colour_values(cube, cube->c);
	cube->f_colours = retrieve_colour_values(cube, cube->f);
}

static char *check_textures(char *elem, int *ret_value)
{
	char	**dest;
	int		fd;

	dest = ft_split_isspace(elem);
	fd = open(dest[1], O_RDONLY);
	if (fd == -1 || ft_arraylen(dest) > 2)
	{
		*ret_value = 6;
		free(elem);
		return (NULL);
	}
	close(fd);
	free(elem);
	elem = ft_strdup(dest[1]);
	ft_arrayfree(dest);
	return (elem);
}

static char *check_ceiling_floor(char *elem, int *ret_value)
{
    char	**dest;
	int		i;
	int		j;
	
	i = 0;
	dest = ft_split_isspace(elem);
	i = 0;
	free(elem);
	elem = NULL;
	while (dest[++i])
	{
		j = -1;
		while (dest[i][++j])
		{
			if (!ft_isdigit(dest[i][j]) && dest[i][j] != ',')
			{
				ft_arrayfree(dest);
				*ret_value = 7;
				return (NULL);
			}
		}
		elem = ft_strjoin_dol(elem, dest[i]);
	}
	ft_arrayfree(dest);
	return (elem);
}

void	parse_cube(t_cub *cube)
{
	int	ret_value;
	
	ret_value = -1;
	cube->no = check_textures(cube->no, &ret_value);
	cube->so = check_textures(cube->so, &ret_value);
	cube->we = check_textures(cube->we, &ret_value);
	cube->ea = check_textures(cube->ea, &ret_value);
	if (ret_value != -1)
    	ft_free_exit(ret_value, cube);
    cube->c = check_ceiling_floor(cube->c, &ret_value);
	cube->f = check_ceiling_floor(cube->f, &ret_value);
	if (ret_value != -1)
    	ft_free_exit(ret_value, cube);
	check_colour_values(cube);
}
