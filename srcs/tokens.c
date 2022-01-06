/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:11:43 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/06 16:30:37 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_is_token(char *arg)
{
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
	else
		return (0);
}

char	*msh_generate_tokens(int specials, int num)
{
	char	*str;
	char	*tmp;
	char	*result;
	size_t	i[2];

	if (specials == 12)
		str = "%S_QOUTES";
	else if (specials == 13)
		str = "%QUOTES";
	else if (specials == 14)
		str = "%D_QUOTES";
	else if (specials == 15)
		str = "%CURL_BRACES";
	else if (specials == 16)
		str = "%DOLLAR_BRACES";
	tmp = ft_itoa(num);
	i[0] = ft_strlen(str);
	i[1] = ft_strlen(tmp);
	result = ft_calloc(i[0] + i[1] + 2, sizeof(char));
	ft_strncat(result, str, i[0]);
	ft_strncat(result, tmp, i[0] + i[1] + 2);
	result[ft_strlen(result)] = '%';
	result[ft_strlen(result) + 1] = '\0';
	ft_strdel(&tmp);
	return (result);
}

t_arg	*msh_get_token_value(t_command *cmd, char *token)
{
	int		stop_int;
	t_arg	*tok;

	stop_int = 0;
	tok = cmd->args_token;
	while (!ft_isdigit(token[stop_int]))
		stop_int++;
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

void	msh_exchange_token_value(t_command *cmd, int index)
{
	t_arg	*tmp;

	tmp = msh_get_token_value(cmd, cmd->args[index]);
	ft_strdel(&cmd->args[index]);
	cmd->args[index] = tmp->value;
}
