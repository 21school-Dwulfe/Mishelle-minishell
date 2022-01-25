/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tilda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:19:18 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/26 00:18:05 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_token_tilda_name(char *str, int *index)
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

int	msh_conditions_tilda(char *str, int *i)
{
	if (str[*i] == '~' && (*i == 0 || str[*i - 1] == ' ')
		&& (str[*i + 1] == '/' || str[*i + 1] == ' ' || str[*i + 1] == '\0'))
		return (TILDA);
	else
		return (0);
}

char	*msh_token_tilda_value(char *arg)
{
	char	*env_value[2];

	ft_bzero(env_value, sizeof(char *) * 2);
	if (arg[0] == '~' && arg[1] == '\0')
		env_value[0] = ft_strdup(msh_get_env_by_key(g_info.env, "HOME"));
	else if (arg[0] == '~' && arg[1] == '/')
	{
		env_value[1] = msh_get_env_by_key(g_info.env, "HOME");
		env_value[0] = ft_strndup_se(env_value[1],
				ft_strlen(env_value[1]) + ft_strlen(arg + 1), 0);
		ft_strncat(env_value[0], arg + 1, ft_strlen(env_value[1])
			+ ft_strlen(arg + 1) + 2);
	}
	return (env_value[0]);
}

void	msh_convert_tilda(char **value, char *name)
{
	ft_strdel(value);
	*value = msh_token_tilda_value(name);
}
