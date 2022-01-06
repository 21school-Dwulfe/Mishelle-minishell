/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_side_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/06 17:39:47 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_specials_cut(char **str, int *i, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *i, '\0', sizeof(char) * end);
	tmp = *str;
	*str = msh_concat_str(*str, len, NULL);
	ft_strdel(&tmp);
	(*i)--;
}

void    msh_specials_replace(char **str, char *insertion, int *start, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *start, '\0', sizeof(char) * end);
	tmp = *str;
	*str = msh_concat_str(*str, len, insertion);
	ft_strdel(&tmp);
	(*start)--;
}


void	msh_specify_token(int *length, char *str, int specials)
{
	char		*name;
	char		*value;
	t_arg		*arg;
	t_command	*cmd;

	cmd = msh_last_cmd();
	value = g_info.func[specials](str, length);
	arg = msh_create_token(NULL, value, g_info.num_token++, specials);
	if (ft_strchr(value, '$'))
	{
		name = ft_strdup(value);
		if (specials != QUOTES)
			msh_evaluate_env_if_exist(&value, g_info.env);
	}
	msh_add_token(cmd, arg);
}

void	msh_choose_effect(char **str, int *i, int specials)
{
	int		len;
	t_arg	*arg;
	
	arg = msh_last_token();
	len = (int)ft_strlen(arg->value);
	if (specials == 11 || specials == 12
		|| specials == 13 || specials == 14 || specials == 15)
		msh_specials_replace(str, arg->pseudo, i, *i + len);
}