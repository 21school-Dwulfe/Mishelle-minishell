/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consitions_double_specials.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:24:29 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 19:24:54 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_conditions_d_amp(char *str, int *i)
{
	if (str[*i] == '&' && str[*i + 1] == '&')
		return (DOUBLE_AMP);
	else
		return (0);
}

int	msh_conditions_d_pipe(char *str, int *i)
{
	if (str[*i] == '|' && str[*i + 1] == '|')
		return (DOUBLE_PIPE);
	else
		return (0);
}

int	msh_conditions_curl_braces(char *str, int *i)
{
	if (str[*i] == '(')
		return (CURL_BRACES);
	else
		return (0);
}
