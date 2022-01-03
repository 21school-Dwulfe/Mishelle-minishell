#include "../includes/main.h"

static char  *msh_fill_in(char *arg, int size, char *insertion, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (i[3] || i[5])
	{
		tmp = ft_calloc(sizeof(char), (i[3] + i[5] + 1));
		while (i[1] < i[0])
		{
			tmp[i[1]] = arg[i[1]];
			i[1]++;
		}
		while (insertion && insertion[i[4]])
		{
			tmp[i[1]] = insertion[i[4]];
			i[1]++;
			i[4]++;
		}
		while (++i[2] + i[4] <= size)
		{
			char c = arg[i[2]];
			tmp[i[1]] = c;
			i[1]++;
		}
	}
	return (tmp);
}

/**
 * @brief 
 * 
 * @param arg 
 * @param size  - size of whole str with nulls
 * @param insertion - string which need to be inserted
 * @return char* 
 */
char	*msh_concat_str(char *arg, int size , char *insertion)
{
	int		i[6];
	
	ft_bzero(i, sizeof(int) * 6);
	i[0] = -1;
	while (arg[++i[0]])
		i[3]++;
	i[2] = size;
	while (--i[2] > i[0] && arg[i[2]])
		i[3]++;
	i[5] = ft_strlen(insertion);
	size += i[5];
	return (msh_fill_in(arg, size, insertion, i));
}

char	**msh_concat_args(char **args, int size)
{
	int		i[4];
	char	**tmp;

	tmp = NULL;
	ft_bzero(i, sizeof(int) * 4);
	i[0] = -1;
	while (args[++i[0]] && ft_strcmp(args[i[0]] ,""))
		i[3]++;
	i[2] = size;
	while (--i[2] > i[0] && args[i[2]] && ft_strcmp(args[i[2]] ,""))
		i[3]++;
	if (i[3])
	{
		tmp = ft_calloc(sizeof(char *), (i[3] + 1));
		while (i[1] < i[0])
		{
			tmp[i[1]] =  args[i[1]]; //tmp[k];
			i[1]++;
		}
		while (++i[2] < size)
		{
			tmp[i[1]] = args[i[2]]; //;t; //tmp[k];
			i[1]++;
		}
		tmp[i[3]] = NULL;
	}
	return (tmp);
}

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
	return (ft_strndup_se(str + first + 1 - reg, i[0] - 1 + (2 * reg), 0));
}
