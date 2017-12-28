#include "libft.h"

char	*ft_strtolower(char *str)
{
	char	*str_pointer;

	str_pointer = str;
	while (*str)
	{
		if (*str >= 65 && *str <= 90)
			*str += 32;
		str += 1;
	}
	return (str_pointer);
}
