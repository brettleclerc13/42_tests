/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:56:49 by ehouot            #+#    #+#             */
/*   Updated: 2024/01/10 18:22:48 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_path(char *s1, char *s2, bool free_first_param)
{
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;
	char	*dest;

	j = 0;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = ft_calloc(lens1 + lens2 + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	while (s1 && ++i < lens1)
		dest[i] = s1[i];
	while (s2 && j < lens2)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (free_first_param)
		free(s1);
	return (dest);
}

char	*ft_strjoin_dol(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;
	char	*dest;

	j = 0;
	i = -1;
	if (!s1)
		return (ft_strdup(s2));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = ft_calloc(lens1 + lens2 + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	while (s1 && ++i < lens1)
		dest[i] = s1[i];
	while (s2 && j < lens2)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	*ft_stradd_char(char *s1, char c)
{
	size_t	i;
	char	*dest;

	i = -1;
	if (!s1)
		dest = ft_calloc(2, sizeof(char *));
	else
		dest = ft_calloc(ft_strlen(s1) + 2, sizeof(char *));
	if (!dest)
		return (NULL);
	if (!s1)
	{
		dest[0] = c;
		dest[1] = '\0';
		return (dest);
	}
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = c;
	dest[i] = '\0';
	free(s1);
	return (dest);
}
