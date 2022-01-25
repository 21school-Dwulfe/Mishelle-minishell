/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:43:47 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 21:42:46 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_cut_set(char **src, char *set)
{
	int		i;
	int		len[2];
	char	*str;

	i = 0;
	if (!src || !set)
		return ;
	str = *src;
	len[0] = ft_strlen(set);
	while (str[i])
	{
		if (!ft_strncmp(str + i, set, len[0]))
		{
			len[1] = ft_strlen(str);
			ft_memset(str + i, '\0', len[0]);
			*src = msh_concat_str(str, len[1], NULL);
			ft_strdel(&str);
			str = *src;
			i -= len[0];
		}
		i++;
	}
}

//if (str && *i - 1 >= 0)
void	msh_cut_effect(char **str, int *i, int sp)
{
	t_command	*command;
	t_arg		*tok;
	char		*prev_word;

	command = msh_last_cmd();
	prev_word = msh_get_prev_word(*str, *i, "|;<> ");
	if (msh_is_token(prev_word))
	{
		tok = msh_get_token_value(command, prev_word);
		if (str[0][*i + 2] == ' ')
			tok->is_prefix = 0;
	}
	ft_strdel(&prev_word);
	if (sp == 25)
		msh_specials_cut(str, i, 1);
	else if (sp == 22 || sp == 23)
		msh_specials_cut(str, i, 2);
	else if (sp == 26)
	{
		msh_specials_cut(str, i, 1);
		(*i) += 2;
	}
	(*i)--;
}

void	msh_side_effect(char **str, int *i, int *sp)
{
	if (*sp == -1)
	{
		(*i)++;
		return ;
	}
	if (*sp == 10 || *sp == 11)
		msh_specials_cut(str, i, 2);
	if (((*sp >= 4 && *sp < 21) && *sp != 10 && *sp != 11 && *sp != 16)
		|| *sp == 7)
		msh_common_side_effect(str, i, *sp);
	if (*sp == 15)
		msh_specials_replace(str, "minishell ", i, 1);
	if (*sp > 21)
		msh_cut_effect(str, i, *sp);
	if (ft_strlen(*str) == 0)
		*sp = -1;
}
