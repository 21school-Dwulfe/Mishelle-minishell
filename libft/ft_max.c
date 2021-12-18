#include "libft.h"

int	*ft_max(int *arr, int size)
{
	int i;
	int *max;

	i = 0;
	max = NULL;
	while (i < size)
	{
		if (max == NULL || arr[i] > *max)
			*max = arr[i];
		i++;
	}
	return (max);
}
