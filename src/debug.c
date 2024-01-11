/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:58:43 by brettlecler       #+#    #+#             */
/*   Updated: 2024/01/11 17:24:49 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_map(t_cub *cube)
{
	int	i;

	i = -1;
	printf("\n--- CUBE MAP ---\n");
	while (cube->map[++i])
		printf("%s", cube->map[i]);
}

void	print_elements(t_cub *cube)
{
	printf("\n--- CUBE ELEMENTS ---\n");
	printf("NO: %s", cube->no);
	printf(" | SO: %s", cube->so);
	printf(" | WE: %s", cube->we);
	printf(" | EA: %s", cube->ea);
	printf(" | C: %s", cube->c);
	printf(" | F: %s\n", cube->f);
}

void	print_colours(t_cub *cube)
{
	printf("\n--- CUBE COLOURS ---\n");
	printf("ceiling R: %i\n", cube->c_colours->r);
	printf("ceiling G: %i\n", cube->c_colours->g);
	printf("ceiling B: %i\n", cube->c_colours->b);
	printf("floor R: %i\n", cube->f_colours->r);
	printf("floor G: %i\n", cube->f_colours->g);
	printf("floor B: %i\n", cube->f_colours->b);
}