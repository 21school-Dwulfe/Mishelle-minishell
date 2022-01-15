/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:11:43 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 14:50:08 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_is_token(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "QUOTES", 6))
		return (1);
	else if (!ft_strncmp(arg, "D_QUOTES", 8))
		return (1);
	else if (!ft_strncmp(arg, "S_QOUTES", 8))
		return (1);
	else if (!ft_strncmp(arg, "CURL_BRACES", 11))
		return (1);
	else if (!ft_strncmp(arg, "DOLLAR_BRACES", 13))
		return (1);
	else if (!ft_strncmp(arg, "DOLLAR", 6))
		return (1);
	else if (!ft_strncmp(arg, "SLASH", 5))
		return (1);
	else
		return (0);
}

char	*msh_generate_tokens(int specials, int num)
{
	char	*str;
	char	*tmp;
	char	tmp1[8];
	char	*result;
	size_t	i[2];

	if (specials == S_QOUTES)
		str = " S_QOUTES";
	else if (specials == QUOTES)
		str = " QUOTES";
	else if (specials == D_QUOTES)
		str = " D_QUOTES";
	else if (specials == CURL_BRACES)
	{
		tmp1[0] = -1;
		tmp1[2] = '\0';
		str = tmp1;//" CURL_BRACES";
	}
	else if (specials == DOLLAR_BRACES)
		str = " DOLLAR_BRACES";
	else if (specials == DOLLAR)
		str = " DOLLAR";
	else if (specials == SLASH)
		str = " SLASH";
	tmp = ft_itoa(num);
	i[0] = ft_strlen(str);
	i[1] = ft_strlen(tmp);
	result = ft_calloc(i[0] + i[1] + 3, sizeof(char));
	ft_strncat(result, str, i[0]);
	ft_strncat(result, tmp, i[0] + i[1] + 3);
	result[ft_strlen(result)] = '%';
	result[ft_strlen(result)] = ' ';
	ft_strdel(&tmp);
	return (result);
}

t_arg	*msh_get_token_value(t_command *cmd, char *token)
{
	int		stop_int;
	t_arg	*tok;

	stop_int = 0;
	tok = cmd->args_token;
	while (token[stop_int] && !ft_isdigit(token[stop_int])
		&& token[stop_int] != ' ')
		stop_int++;
	if (token[stop_int] == '\0')
		return (NULL);
	while (tok)
	{
		if (tok->order == ft_atoi(token + stop_int))
			break ;
		tok = tok->next;
	}
	return (tok);
}

t_arg	*msh_last_token(void)
{
	return (msh_last_cmd()->args_token->prev);
}
