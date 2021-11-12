#include "libft.h"

int	ft_index_of(char *line, int c)
{
	int i;

	i = 0;
	if (!line)
		return (-2);
	while (line[i])
	{
		if ((unsigned char)line[i] - (unsigned char)c == 0)
			return (i);
		i++;
	}
	return (-1);
}
