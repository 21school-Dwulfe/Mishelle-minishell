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
	else if (i > 0 )
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
		if (flag == 0 && check_is_opened(str[i]) && ++i)
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

char	*msh_get_quotes_str(char *str, int *i)
{
	int start;
	char *result;

	start = *i;
	while (check_is_opened(str[*i]))
		*i = *i + 1;
	*i = *i + 1;
	result = ft_strndup(str + start, *i - 1 - start);
	return (result);
}

char *ft_str_smart_join(char *s1, char *s2)
{
	if (s1 == NULL )
		return (s2);
	return (ft_strjoin(s1, s2));
}

char	**msh_split(char *str, int c)
{
	int		i;
	int		j;
	int		start;
	char	**result;
	int		counter;
	int 	concat;
	char	*tmp[2];

	i = 0;
	j = 0;
	concat = 1;
	ft_bzero(tmp, sizeof(char) * 2);
	counter = count_str(str, c);
	result = ft_calloc(counter + 1, sizeof(char *));
	while (str[i])
	{	
		while (str[i] && str[i] == c)
				i++;
		while (str[i] && str[i] != c)
		{
			if (check_is_opened(str[i]) && ++i)
			{
				tmp[0] = msh_get_quotes_str(str, &i);
				if (tmp[0] != NULL && result[j])
				{
					tmp[1] = result[j];
					result[j] = ft_strjoin(tmp[1], tmp[0]);
					ft_strdel(tmp[1]);
					ft_strdel(tmp[0]);
				}
				else
					result[j] = tmp[0];
			}
			if ((result[j] && str[i] == c) || str[i] == '\0')// if next char after quotes == space
				break ;
			if (str[i] && str[i] != '\'' && str[i] != '\"')
			{
				start = i;
				while(str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != c)
					i++;
				if (result[j] != 0 && start != i)
				{
					tmp[1] = result[j];
					tmp[0] = ft_strndup(str + start, i - start);
					result[j] = ft_str_smart_join(tmp[1], tmp[0]);
					ft_strdel(tmp[1]);
					ft_strdel(tmp[0]);
				}
				else if (start != i)
					result[j] = ft_strndup(str + start, i - start);
			}
			
		}
		if (j > 0 && result[j - 1] == NULL)
				ft_arrstr_del(result, j);
		else
			j++;
	}
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