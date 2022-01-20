/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:22:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/20 22:29:05 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_token_wildcard_value(char *str, int *index)
{
	int		i[2];
	char	*result;
	
	i[0] = *index;
	i[1] = *index;
	result = NULL;
	while (i[0] - 1 > -1 && str[i[0] - 1] != ' ')
		i[0]--;
	while (str[i[1] + 1] && !ft_strchr(" |;<>&", str[i[1]]))
		i[1]++;
	if (i[0] != *index || i[1] != *index)
		result = ft_strndup(str + i[0], i[1] - i[0]);
	return (result);
}

char *msh_wildcard(char *path, char *pattern)
{
	int				len;
	struct dirent	*ent;
	DIR				*dir;
	char			*result;
  
	(void)pattern;
	if (!path)
		return (NULL);
	result = NULL;
	dir = opendir(path);
	while (dir != NULL)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (*ent->d_name != '.')
		{
			
			len = ft_strlen(result)	+ ft_strlen(ent->d_name) + 2;
			if (!result)
				result = ft_strdup(ent->d_name);
			else
			{
				printf("%s\n", ent->d_name);
				result = ft_realloc(result, len);
				result[ft_strlen(result)] = ' ';
				result = ft_strncat(result, ent->d_name, len);
			}
		}
	}
	closedir(dir);
	return (result);
}

char	*msh_token_wildcard(char *str, int *i)
{
	char	*result;
	char	*path;
	char	*pattern;
	char	*tmp_m[3];
	
	(void)pattern;
	(void)str;
	(void)i;
	result = NULL;
	path = NULL;
	ft_bzero(tmp_m, sizeof(char) * 3);
	tmp_m[0] = msh_token_wildcard_value(str, i);
	if (!tmp_m[0])
		path = msh_get_env_by_key(g_info.env, "PWD");
	else if (*i - 1 > -1 && str[*i - 1] == '/')
	{
		path = ft_strndup_se(tmp_m[0], 0, '*');
	}
	if (path)
		result = msh_wildcard(path, tmp_m[0] + ft_index_of(tmp_m[0], '*', 0));
	return (result);
}


