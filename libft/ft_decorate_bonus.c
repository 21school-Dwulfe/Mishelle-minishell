#include "libft.h"

char	*ft_decorate(char *src, char *begining, char *end)
{
	char	*result;
	int		l[6];

	ft_bzero(l, sizeof(int) * 6);
	l[0] = ft_strlen(src) + ft_strlen(begining) + ft_strlen(end) + 1;
	result = malloc(sizeof(char) * l[0]);
	result[l[0] - 1] = '\0';
	l[1] = ft_strlen(begining);
	while (l[2] < l[1])
    {
		result[l[2]] = begining[l[2]];
        l[2]++;
    }
	l[3] = ft_strlen(src);
	while (l[4] < l[3])
    {
		result[l[2] + l[4]] = src[l[4]];
        l[4]++;
    }
	l[5] =ft_strlen(end);
	while (l[6] < l[5])
    {
		result[l[2] + l[4] + l[6]] = src[l[6]];	
        l[6]++;
    }
	return (result);
}

int main(void)
{
    char    *res;
 
    res = ft_decorate("text", "<", "//>");
    ft_putendl_fd(res, 1);
}