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

#include "../includes/main.h"

char	*msh_token_dollar(char *str, int *index, char **value_arg)
{
	int		i;
	char	*result;

	i = *index;
	i++;
	while (str[i] && str[i] != ' ' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	result = ft_strndup_se(str + *index, i - *index, 0);
	value_arg = NULL;
	(void)value_arg;
	return (result);
}

char	*msh_token_d_quotes(char *str, int *index, char **value_arg)
{
	char	*result;

	result = msh_get_str_inside(str + *index, "\"", 0);
	value_arg = NULL;
	(void)value_arg;
	return (result);
}

char	*msh_token_quotes(char *str, int *index, char **value_arg)
{
	char	*result;

	result = msh_get_str_inside(str + *index, "\'", 0);
	value_arg = NULL;
	(void)value_arg;
	return (result);
}

char	*msh_curl_braces(char *str, int *index, char **value_arg)
{
	(void)str;
	(void)index;
	(void)value_arg;
	return (NULL);
}

char	*msh_dollar_braces(char *str, int *index, char **value_arg)
{
	(void)str;
	(void)index;
	(void)value_arg;
	return (NULL);
}
