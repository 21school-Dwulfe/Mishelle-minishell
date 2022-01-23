/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:31:49 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 23:28:21 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	msh_check(char **args, char **ar, int size, int *i)
{
	ft_bzero(i, sizeof(int) * 6);
	i[0] = -1;
	while (args[++i[0]] && ft_strcmp(args[i[0]], ""))
		i[3]++;
	i[2] = size;
	while (--i[2] > i[0] && args[i[2]] && ft_strcmp(args[i[2]], ""))
		i[3]++;
	i[4] = ft_str_count(ar);
	size += i[4];
}

char	**msh_concat_insert_args(char **args, char **ar, int size)
{
	int		i[6];
	char	**tmp;

	if (!args)
		return (NULL);
	tmp = NULL;
	msh_check(args, ar, size, i);
	tmp = ft_calloc(sizeof(char *), (i[3] + 1 + i[4]));
	while (i[1] < i[0])
	{
		tmp[i[1]] = args[i[1]];
		i[1]++;
	}
	while (ar && ar[i[5]])
	{
		tmp[i[1]] = ar[i[5]];
		i[1]++;
		i[5]++;
	}
	while (++i[2] + i[5] < size)
	{
		tmp[i[1]] = args[i[2]];
		i[1]++;
	}
	return (tmp);
}
