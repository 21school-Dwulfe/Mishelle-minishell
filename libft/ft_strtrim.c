#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (!(ft_strchr(set, *s1)))
			break ;
		s1++;
	}
	result = (char *)s1 + (ft_strlen(s1) - 1);
	while (result >= s1)
	{
		if (!(ft_strchr(set, *result)))
			break ;
		result--;
	}
	return (ft_strndup(s1, ++result - s1));
}
