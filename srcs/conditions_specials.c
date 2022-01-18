/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_specials.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:05:05 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/18 16:36:09 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_conditions_wildcard(char *str, int *i)
{
	if (str[*i] == '*')
		return (WILDCARD);
	else
		return (0);
}

int msh_conditions_semicolon(char *str, int *i)
{
	if (*i > 0 && str[*i] == ';')
		return (SEMICOLON);
	else
		return (0);
}

int msh_conditions_pipe(char *str, int *i)
{
	if (str[*i] == '|' && str[*i + 1] != '|')
		return (PIPE);
	else
		return (0);
}

int msh_conditions_eof(char *str, int *i)
{
	if (str[*i + 1] == '\0')
		return (-1);
	else
		return (0);
}

int msh_conditions_dollar(char *str, int *i)
{
	if (str[*i] == '$' && str[*i + 1] != '\0' && str[*i + 1] != ' ')
		return (DOLLAR);
	else
		return (0);
}