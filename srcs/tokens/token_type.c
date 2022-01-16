/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:17:48 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:17:50 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_token_dollar(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	while (str[i] && str[i] != ' ' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	result = ft_strndup_se(str + *index, i - *index, 0);
	return (result);
}

char	*msh_token_d_quotes(char *str, int *index)
{
	char	*result;

	result = msh_get_str_inside(str + *index, "\"", 0);
	return (result);
}

char	*msh_token_quotes(char *str, int *index)
{
	char	*result;

	result = msh_get_str_inside(str + *index, "\'", 0);
	return (result);
}

char	*msh_token_wildcard(char *str, int *index)
{
	int	i[2];

	i[0] = *index;
	i[1] = *index;


}

char	*msh_curl_braces(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && str[i] != ')')
		i++;
	result = ft_strndup(str + *index + 1, i - 1);
	return (result);
}

char	*msh_slash(char *str, int *index)
{
	return (ft_strndup(str + *index, 2));
}