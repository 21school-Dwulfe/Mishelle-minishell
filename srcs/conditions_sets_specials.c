/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_sets_specials.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:04 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 15:47:10 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_conditions_dollar_braces(char *str, int *i)
{
	if (str[*i] == '$' && str[*i] == '(')
		return (DOLLAR_BRACES);
	else
		return (0);
}

int	msh_conditions_redirects(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] != '>')
		return (REDIRECT);
	if (str[*i] == '<' && str[*i + 1] != '<')
		return (R_REDIRECT);
	if (str[*i] == '>' && str[*i + 1] == '>')
		return (D_REDIRECT);
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (HEREDOC);
	return (0);
}
