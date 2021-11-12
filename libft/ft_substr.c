#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	char		*str;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len >= start)
	{
		if (len > (s_len - start))
			len = s_len - start;
	}
	else
		len = 0;
	str = ft_strndup(s + start, len);
	return (str);
}
