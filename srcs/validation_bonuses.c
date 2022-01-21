/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonuses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:13:54 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 16:17:28 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_validation_double_amp(char *str, int *i)
{
	char	*tmp[2];
	int		result;

	result = 0;
	tmp[0] = msh_get_prev_word(str, *i, " ");
	tmp[1] = msh_get_next_word(str, *i, " ");
	if (ft_strcmp(tmp[0], "") == 0)
		result = msh_unexpected_token_error("&&", 2);
	else if (ft_strcmp(tmp[1], "") == 0)
		result = -11;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	return (result);
}

int	msh_validation_double_pipe(char *str, int *i)
{
	int		result;
	char	*tmp[2];

	result = 0;
	tmp[0] = msh_get_prev_word(str, *i, " ");
	tmp[1] = msh_get_next_word(str, *i, " ");
	if (ft_strcmp(tmp[0], "") == 0)
		result = msh_unexpected_token_error("||", 2);
	else if (ft_strcmp(tmp[1], "") == 0)
		result = -10;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	return (result);
}
