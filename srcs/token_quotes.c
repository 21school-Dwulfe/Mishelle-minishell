/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:17:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 22:32:10 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// && str[*i + 1] != '\''
int	msh_conditions_quotes(char *str, int *i)
{
	if (str[*i] == '\'')
		return (QUOTES);
	else
		return (0);
}

//&& str[*i + 1] != '\"'
int	msh_conditions_d_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
		return (D_QUOTES);
	else
		return (0);
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
