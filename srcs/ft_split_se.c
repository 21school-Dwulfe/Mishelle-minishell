#include "../includes/main.h"

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

int	count_strs(char	*str, int c)
{
	int	i;
	int flag;
	int count;

	i = -1;
	flag = 0;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			flag = 0;
		else if (flag == 0 && ++count)
			flag = 1;
	}
	return (count);
}

char **ft_split_se(char *str, int c)
{
	int		i;
	int		j;
	int		start;
	char	**result;

	i = 0;
	j = 0;
	result = (char **)malloc(sizeof(char *) * (count_strs(str, c) + 1));
	while (str[i])
	{	
		while (str[i] && str[i] == c)
				i++;
		start = i;
		if (str[i] != c && str[i] != '\0' )
		{	
			while (str[i] && str[i] != c)
				i++;
			result[j] = ft_strndup(str + start, i - start);
			j++;
		}
		if (result[j - 1] == NULL)
				ft_freee(result, j);
	}
	result[j] = "\0";
	return (result);
}

// int main(void)
// {
// 	int i = 0;
// 	char	**chstr;

// 	chstr = ft_split_se("dfghj asd asdfg", ' ');
// 	(void)chstr;
// 	while (ft_strcmp(chstr[i], "\0"))
// 	{
// 		printf("|%s|\n", chstr[i]);
// 		free(chstr[i]);
// 		i++;
// 	}

// 	free(chstr);
// 	chstr = NULL;
	
// 	return (0);
// }