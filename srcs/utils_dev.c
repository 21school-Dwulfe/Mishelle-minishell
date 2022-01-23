/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:28:22 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 23:37:02 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_tokens_pseudo(int sp)
{
	char	*tmp1;

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
	if (str[0] <= -13 && str[0] >= -18 && str[1] == '%' && str[2] == '\0')
		return (-str[0]);
	return (0);
}

int	msh_tok_pseudo_reader_dev(char *arg)
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
	else if (!ft_strncmp(arg, "RD_REDIRECT", 11))
		return (1);
	else if (!ft_strncmp(arg, "WILDCARD", 8))
		return (1);
	else if (!ft_strncmp(arg, "TILDA", 5))
		return (1);
	else
		return (0);
}

char	*msh_tokens_pseudo_dev(int specials)
{
	char	*str;

	if (specials == S_QOUTES)
		str = " S_QOUTES";
	else if (specials == QUOTES)
		str = " QUOTES";
	else if (specials == D_QUOTES)
		str = " D_QUOTES";
	else if (specials == CURL_BRACES)
		str = " CURL_BRACES";
	else if (specials == DOLLAR_BRACES)
		str = " DOLLAR_BRACES";
	else if (specials == DOLLAR)
		str = " DOLLAR";
	else if (specials == SLASH)
		str = " SLASH";
	else if (specials == HEREDOC)
		str = " RD_REDIRECT";
	else if (specials == WILDCARD)
		str = " WILDCARD";
	else if (specials == TILDA)
		str = " TILDA";
	return (ft_strdup(str));
}
