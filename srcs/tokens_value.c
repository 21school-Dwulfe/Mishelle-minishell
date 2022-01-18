/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:17:48 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/18 23:08:14 by dwulfe           ###   ########.fr       */
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

char	*msh_token_redirect(char *str, int *index)
{
	int		i[2];
	char	*result;
	int		word;
	char	c;

	i[0] = *index;
	i[1] = *index;
	word = 0;
	result = NULL;
	c = str[i[0]];
	while (i[0] - 1 > -1 && str[i[0] - 1] != ' ')
		i[0]--;
	while (str[i[1]] && str[i[1]] == c)
		i[1]++;
	while (str[i[1]] && str[i[1]] == ' ')
	{
		if (str[i[1] + 1] != '\0' && str[i[1] + 1] != ' ')
			word = i[1];
		i[1]++;
	}
	while (str[i[1]] && !ft_strchr(" |;<>&", str[i[1]]))
		i[1]++;
	if (word && (i[0] != *index || i[1] != *index))
		result = ft_strndup(str + word, i[1] - word);
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

char	*msh_slash(char *str, int *index)
{
	return (ft_strndup(str + *index, 2));
}