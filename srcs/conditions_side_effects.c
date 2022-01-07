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

void	msh_evaluate_var(char **value, int specials)
{
	char	*res;

	if (specials != QUOTES)
	{
		if (ft_strlen(*value) > 0 && *value[1] != '?')
			res = msh_evaluate_env_arg(*value, g_info.env);
		else if (ft_strlen(*value) > 0 && *value[1] == '?')
			res = msh_dollar_error_case(value, NULL);
		ft_swap_strs(&res, value);
		ft_strdel(&res);
	}
}

void	msh_specify_token(int *length, char *str, int specials)
{
	char		*name;
	char		*value;
	t_arg		*arg;
	t_command	*cmd;

	cmd = msh_last_cmd();
	name = NULL;
	value = g_info.func[specials](str, length);
	if (ft_strchr(value, '$'))
	{
		name = ft_strdup(value);
		msh_evaluate_var(&value, specials);
	}
	arg = msh_create_token(name, value, g_info.num_token++, specials);
	msh_add_token(cmd, arg);
	if (msh_is_token(msh_get_prev_word(str, *length, ";|<> ")) && arg->prev->is_prefix)
		arg->has_prefix = 1;
	else if (*length - 1 > -1 && str[*length] != ' ')
		arg->has_prefix = 1;
}

void	msh_choose_effect(char **str, int *i, int specials)
{
	int		len;
	t_arg	*arg;

	if (str == NULL || !i )
		return ;
	msh_specify_token(i, *str, specials);
	arg = msh_last_token();
	len = (int)ft_strlen(arg->value);
	if (specials == 11 || specials == 12
		|| specials == 13 || specials == 14 || specials == 15)
		msh_specials_replace(str, arg->pseudo, i, *i + len);
}