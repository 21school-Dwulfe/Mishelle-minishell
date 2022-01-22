/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:22:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 20:42:40 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_realloc(char *res, struct dirent *ent)
{
	int				len;
	char			*tmp;

	len = ft_strlen(res) + ft_strlen(ent->d_name) + 1;
	if (!res)
		res = ft_strdup(ent->d_name);
	else
	{
		tmp = res;
		res = ft_strjoin(res, ent->d_name);
		ft_strdel(&tmp);
		tmp = res;
		res = ft_strjoin(res, " ");
		ft_strdel(&tmp);
	}
	return (res);
}

char	*msh_token_wildcard_name(char *str, int *index)
{
	int		i[2];
	char	*result;

	i[0] = *index;
	i[1] = *index;
	result = NULL;
	while (i[0] - 1 > -1 && str[i[0] - 1] != ' ')
		i[0]--;
	while (str[i[1]] && !ft_strchr(" |;<>&", str[i[1]]))
		i[1]++;
	if (i[0] != *index || i[1] != *index)
		result = ft_strndup(str + i[0], i[1] - i[0]);
	return (result);
}

// path = "/Users/dwulfe/Mishelle-minishell";
void	msh_wildcard(char *path, char **result)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*res;

	res = *result;
	dir = opendir(path);
	while (dir != NULL)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (*ent->d_name != '.')
			res = msh_realloc(res, ent);
	}
	*result = res;
}

char	*msh_slash(char *str, int *index)
{
	return (ft_strndup(str + *index, 2));
}

int	msh_conditions_wildcard(char *str, int *i)
{
	if (str[*i] == '*')
		return (WILDCARD);
	else
		return (0);
}
