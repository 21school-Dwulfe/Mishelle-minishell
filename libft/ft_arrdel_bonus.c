#include "libft.h"

char	**ft_freee(char **dst, int s_counter)
{
	while (s_counter > 0)
	{
		s_counter--;
		free((void *)dst[s_counter]);
	}
	free(dst);
	return (NULL);
}
