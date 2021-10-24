#include "libft.h"

void	ft_strdel(char	*ptr)
{
	if (ptr)
	{
		free(ptr);
	}
	ptr = NULL;
}
