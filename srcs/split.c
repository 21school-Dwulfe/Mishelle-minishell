#include "../includes/main.h"

int	check_is_opened(char c)
{
	static int i;
	static int ch;

	if (c == 0)
		return (0);
	if (i == 0 && (c == '\'' || c == '\"'))
	{
		i = 1;
		ch = c;
	}
	else if (i > 0 && c != ch)
		return (ch);
	else if (i > 0)
	{
		i = 0;
		ch = 0;
	}
	return (ch);
}

int	count_str(char	*str, int c)
{
	int	i;
	int flag;
	int count;

	i = -1;
	flag = 0;
	count = 0;
	while (str[++i])
	{
		if (check_is_opened(str[i]) && ++i)
		{
			while (check_is_opened(str[i]))
				i++;
			count++;
			flag = 0;
		}
		else if (str[i] == c)
			flag = 0;
		else if (flag == 0)
		{
			count++;
			flag = 1;
		}
	}
	return (count);
}

char	**msh_split(char *str, int c)
{
	int		i;
	int		j;
	int		start;
	char	**result;

	i = 0;
	j = 0;
	result = (char **)malloc(sizeof(char *) * (count_str(str, c) + 1));
	while (str[i])
	{	
		while (str[i] && str[i] == c)
				i++;
		start = i;
		if (check_is_opened(str[i]) && ++i)
		{
			while (str[i] && check_is_opened(str[i]))
				i++;
			result[j] = ft_strndup(str + start, (++i - start));
			j++;
		}
		else if (str[i] != c && str[i] != '\0' )
		{	
			while (str[i] && ((str[i] != '\'') & (str[i] != '\"')) && str[i] != c)
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

// 	chstr = msh_split("dfghj asd asdfg", ' ');
// 	while (ft_strcmp(chstr[i], "\0"))
// 	{
// 		printf("|%s|\n", chstr[i]);
// 		free(chstr[i]);
// 		i++;
// 	}

// 	free(chstr);
// 	//chstr = NULL;
	
// 	return (0);
// }