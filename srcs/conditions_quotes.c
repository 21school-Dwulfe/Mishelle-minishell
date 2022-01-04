/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:52 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:04:54 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int msh_conditions_d_quotes_close(char *str, int *i)
{
	if (str[*i] == '\"' && str[*i + 1] == '\"')
		return (22);
	else
		return (0);
}

int msh_conditions_quotes_close(char *str, int *i)
{
	if (str[*i] == '\'' && str[*i + 1] == '\'')
		return (23);
	else
		return (0);
}

int msh_conditions_quotes(char *str, int *i)
{
	if (str[*i] == '\'' && str[*i + 1] != '\'')
		return (QUOTES);
	else
		return (0);
}

int msh_conditions_d_quotes(char *str, int *i)
{
	if (str[*i] == '\"' && str[*i + 1] != '\"')
		return (D_QUOTES);
	else
		return (0);
}
