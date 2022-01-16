/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:09:05 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*msh_fill_in(char *arg, int size, char *insertion, int *i)
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
			tmp[i[1]] = arg[i[2]];
			i[1]++;
		}
	}
	return (tmp);
}

char	*msh_concat_str(char *arg, int size, char *insertion)
{
	int	i[6];

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

	if (!args)
		return (NULL);
	tmp = NULL;
	ft_bzero(i, sizeof(int) * 4);
	i[0] = -1;
	while (args[++i[0]] && ft_strcmp(args[i[0]], ""))
		i[3]++;
	i[2] = size;
	while (--i[2] > i[0] && args[i[2]] && ft_strcmp(args[i[2]], ""))
		i[3]++;
	tmp = ft_calloc(sizeof(char *), (i[3] + 1));
	while (i[1] < i[0])
	{
		tmp[i[1]] = args[i[1]];
		i[1]++;
	}
	while (++i[2] < size)
	{
		tmp[i[1]] = args[i[2]];
		i[1]++;
	}
	return (tmp);
}

char *msh_get_str_inside(char *str, char *set, int reg)
{
	int			f;
	int 		i[2];

	f = -1;
	ft_bzero(i, sizeof(int) * 2);
	if (!set || !str || reg > 1 || reg < 0)
		return (NULL);
	while (str[i[0]])
	{
		i[1] = 0;
		while (f == -1 && set[i[1]])
		{
			if ((unsigned char)str[i[0]] - (unsigned char)set[i[1]] == 0)
			{
				f = i[0];
				i[0]++;
				break;
			}
			i[1]++;
		}
		if (f != -1 && !((unsigned char)str[i[0]] - (unsigned char)str[f]))
			break ;
		i[0]++;
	}
	return (ft_strndup_se(str + f + 1 - reg, i[0] - 1 + (2 * reg), 0));
}

char	**msh_replace_and_copy(char **args, char *new, int index)
{
	int	i;
	int len;
	char **arr;
	
	arr = NULL;
	i = 0;
	len = ft_str_count(args);
	arr = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (i == index)
		{
			arr[i] = new;
			ft_strdel(&args[index]);
		}
		else
		{
			arr[i] = args[i];
			args[i] = NULL;
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}