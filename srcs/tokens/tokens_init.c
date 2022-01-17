/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:11:43 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char *msh_tokens_pseudo(int sp)
{
	char *tmp1;

	tmp1 = ft_calloc(4, sizeof(char *));
	if (sp != -1)
	{
		tmp1[0] = ' ';
		tmp1[1] = -sp;
		tmp1[2] = '%';
		tmp1[3] = '\0';
	}
	return (tmp1);
}

int	msh_tok_pseudo_reader(char *str)
{
	// -13 -14 -15 -17 -18
	if (str[0] <=  -13 && str[0] >= -18 && str[1] == '%' && str[2] == '\0')
		return (-str[0]);
	return (0);
}

int msh_tok_pseudo_reader_dev(char *arg)
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

int	msh_is_token(char *arg)
{
	if (DEV_TOKENS)
		return (msh_tok_pseudo_reader_dev(arg));
	else
		return (msh_tok_pseudo_reader(arg));
}

t_arg	*msh_last_token(void)
{
	return (msh_last_cmd()->args_token->prev);
}
