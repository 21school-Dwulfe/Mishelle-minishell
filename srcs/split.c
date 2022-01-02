#include "../includes/main.h"

// int	check_is_opened(char c)
// {
// 	static int i;
// 	static int ch;

// 	if (c == 0)
// 		return (0);
// 	if (i == 0 && (c == '\'' || c == '\"'))
// 	{
// 		i = 1;
// 		ch = c;
// 	}
// 	else if (i > 0 && c != ch)
// 		return (ch);
// 	else if (i > 0 )
// 	{
// 		i = 0;
// 		ch = 0;
// 	}
// 	return (ch);
// }

// int	count_str(char	*str, int c)
// {
// 	int	i;
// 	int flag;
// 	int count;

// 	i = -1;
// 	flag = 0;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (flag == 0 && check_is_opened(str[i]) && ++i)
// 		{
// 			while (check_is_opened(str[i]))
// 				i++;
// 			count++;
// 			flag = 0;
// 		}
// 		else if (str[i] == c)
// 			flag = 0;
// 		else if (flag == 0)
// 		{
// 			count++;
// 			flag = 1;
// 		}
// 	}
// 	return (count);
// }

// char	*msh_get_quotes_str(char *str, int *i)
// {
// 	int start;
// 	char *result;

// 	start = *i;
// 	while (check_is_opened(str[*i]))
// 		*i = *i + 1;
// 	*i = *i + 1;
// 	result = ft_strndup(str + start, *i - 1 - start);
// 	return (result);
// }

// char	*ft_str_smart_join(char *s1, char *s2)
// {
// 	if (s1 == NULL && s2)
// 		return (s2);
// 	else if (s1 && s2 == NULL)
// 		return (s1);
// 	return (ft_strjoin(s1, s2));
// }

// char	**msh_split(char *str, int c)
// {
// 	int		i;
// 	int		j;
// 	int		start;
// 	char	**result;
// 	int		counter;
// 	char	*tmp[2];

// 	i = 0;
// 	j = 0;
// 	ft_bzero(tmp, sizeof(char) * 2);
// 	counter = count_str(str, c);
// 	result = (char **)malloc((counter + 1) * sizeof(char *));
// 	ft_bzero(result, (counter + 1) * sizeof(char *));
// 	while (str[i])
// 	{	
// 		while (str[i] && str[i] == c)
// 				i++;
// 		while (str[i] && str[i] != c)
// 		{
// 			if (check_is_opened(str[i]) && ++i)
// 			{
// 				tmp[0] = msh_get_quotes_str(str, &i);
// 				if (tmp[0] != NULL && result[j])
// 				{
// 					tmp[1] = result[j];
// 					result[j] = ft_strjoin(tmp[1], tmp[0]);
// 					ft_strdel(&tmp[1]);
// 					ft_strdel(&tmp[0]);
// 				}
// 				else
// 					result[j] = tmp[0];
// 			}
// 			if ((result[j] && str[i] == c) || str[i] == '\0')// if next char after quotes == space
// 				break ;
// 			if (str[i] && str[i] != '\'' && str[i] != '\"')
// 			{
// 				start = i;
// 				while(str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != c)
// 					i++;
// 				if (result[j] != 0 && start != i)
// 				{
// 					tmp[1] = result[j];
// 					tmp[0] = ft_strndup(str + start, i - start);
// 					result[j] = ft_str_smart_join(tmp[1], tmp[0]);
// 					ft_strdel(&tmp[1]);
// 					ft_strdel(&tmp[0]);
// 				}
// 				else if (start != i)
// 					result[j] = ft_strndup(str + start, i - start);
// 			}
			
// 		}
// 		if (j > 0 && result[j - 1] == NULL)
// 				ft_arrstr_del(result, j);
// 		else if (j < counter)
// 			j++;
// 	}
// 	result[j] = (void *)0;
// 	return (result);
// }


char *msh_get_str_inside(char *str, char *set, int reg)
{
	int			first;
	int 		i[2];

	first = -1;
	ft_bzero(i, sizeof(int) * 2);
	if (!set || !str || reg > 1 || reg < 0)
		return (NULL);
	while (str[i[0]])
	{
		i[1] = 0;
		while (first == -1 && set[i[1]])
		{
			if ((unsigned char)str[i[0]] - (unsigned char)set[i[1]] == 0)
			{
				first = i[0];
				i[0]++;
				break;
			}
			i[1]++;
		}
		if (first != -1
			&& (unsigned char)str[i[0]] - (unsigned char)str[first] == 0)
			break ;
		i[0]++;
	}
	return (ft_strndup_se(str + first + 1 - reg, i[0] - 1 + reg, 0));
}

// int	main(void)
// {
// 	char *str = "as\"\"'$hhhhh'''";

// 	char *s2 = msh_get_str_inside(str, "\'\"", 0);
// 	printf("%s\n", s2);
// 	return (0);
// }

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