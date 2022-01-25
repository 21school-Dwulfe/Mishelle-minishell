/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:17:48 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 21:27:49 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_token_dollar(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	if (str[i] && ft_isdigit(str[i + 1]))
		return (ft_strndup(str + *index, i + 1 - *index));
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

char	*msh_token_curl_braces(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && str[i] != ')')
		i++;
	result = ft_strndup(str + *index + 1, i - 1);
	return (result);
}
