/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_side_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:05:01 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_side_effects(char **str, int *i, int *specials)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (*specials == -1)
	{
		(*i)++;
	}
	if (*specials == 22 || *specials == 23)
	{
		len = ft_strlen(*str);
		ft_memset((*str) + *i, '\0', sizeof(char) * 2);
		tmp = *str;
		*str = msh_concat_str(*str, len, NULL);
		ft_strdel(&tmp);
		(*i)--;
	}
}
