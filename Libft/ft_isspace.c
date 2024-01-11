#include "libft.h"

int ft_isspace(char c)
{
	if (!((c >= 9 && c <= 13)) && !(c == 32))
		return (0);
	else
		return (1);
}
