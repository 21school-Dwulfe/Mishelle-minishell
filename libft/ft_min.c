#include "libft.h"

int	*ft_min(int *arr, int size)
{
	int i;
	int *min;

	i = 0;
	min = NULL;
	while (i < size)
	{
		if (min == NULL || arr[i] < *min)
			*min = arr[i];
		i++;
	}
	return (min);
}
