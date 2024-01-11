#include "libft.h"

static char	*ft_fill(char *dest, char const *s, int i)
{
	int	j;
	int	z;
	int	a;

	z = 0;
	j = 0;
	a = 0;
	while (s[z] && a <= i)
	{
		while (s[z] && ft_isspace(s[z]))
			z++;
		while (s[z] && !ft_isspace(s[z]))
		{
			if (a == i)
			{
				dest[j] = s[z];
				j++;
			}
			z++;
		}
		a++;
	}
	dest[j] = 0;
	return (dest);
}

static int	ft_count_size(char const *s, int i)
{
	int	j;
	int	z;
	int	a;

	z = 0;
	j = 0;
	a = 0;
	while (s[z] && a <= i)
	{
		while (s[z] && ft_isspace(s[z]))
			z++;
		while (s[z] && !ft_isspace(s[z]))
		{
			if (a == i)
				j++;
			z++;
		}
		a++;
	}
	return (j);
}

static int	ft_count(char const *s)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			cpt++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (cpt);
}

char	**ft_split_isspace(char const *s)
{
	char	**dest;
	int		i;
	int		nb_words;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count(s);
	dest = malloc (sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (NULL);
	while (i < nb_words)
	{
		dest[i] = malloc (ft_count_size(s, i) + 1);
		if (!dest[i])
			return (NULL);
		dest[i] = ft_fill(dest[i], s, i);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
