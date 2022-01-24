/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_sets_specials.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:04 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 21:50:19 by dwulfe           ###   ########.fr       */
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
