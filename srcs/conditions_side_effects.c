/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_side_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 19:00:47 by dwulfe           ###   ########.fr       */
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

void    msh_specials_replace(char **str, char *insertion, int *start, int len)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	(void)tmp;
	l = ft_strlen(*str);
	ft_memset((*str) + *start, '\0', sizeof(char) * len);
	tmp = *str;
	*str = msh_concat_str(*str, l, insertion);
	//ft_strdel(&tmp);
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
	char		*value[2];
	char		*tmp[3];
	t_arg		*arg;
	t_command	*cmd;
	int			add;
	int			has_prefix;
	int			is_prefix;

	cmd = msh_last_cmd();
	name = NULL;
	arg = NULL;
	has_prefix = 0;
	is_prefix = 0;
	add = 0;
	ft_bzero(value, sizeof(char *) * 2);
	value[0] = g_info.func[specials](str, length);
	name = ft_strdup(value[0]);
	tmp[0] = msh_get_prev_word(str, *length, ";|<> ");
	arg = msh_get_token_value(cmd, tmp[0]);
	if (arg && msh_is_token(arg->pseudo) && arg->prev->is_prefix)
		has_prefix = 1;
	else if (*length - 1 > -1 && str[*length - 1] != ' ')
		has_prefix = 1;
	if (specials == 13 || specials == 14 || specials == 15)
		add += 2;
	if (*length + (int)ft_strlen(value[0]) + 1 <= (int)ft_strlen(str) && str[*length + (int)ft_strlen(value[0]) + add] != ' ' && 
		(int)ft_strlen(str) && str[*length + (int)ft_strlen(value[0]) + add] != '\0')
		is_prefix = 1;
	ft_strdel(&tmp[0]);
	if (ft_strchr(value[0], '$') && specials != QUOTES)
		msh_evaluate_env_if_exist(value, g_info.env);
	arg = msh_create_token(name, value[0], g_info.num_token++, specials);
	arg->has_prefix = has_prefix;
	arg->is_prefix = is_prefix;
	msh_add_token(cmd, arg);
}

void	msh_choose_effect(char **str, int *i, int specials)
{
	int		len;
	t_arg	*arg;

	if (str == NULL || !i)
		return ;
	arg = NULL;
	len = 0;
	if (specials == -1)
		(*i)++;
	if (specials == 13 || specials == 14 || specials == 15)
		len += 2;
	if (specials == 11 || specials == 12 || specials == 17
		|| specials == 13 || specials == 14 || specials == 15)
	{
		msh_specify_token(i, *str, specials);
		arg = msh_last_token();
		len += (int)ft_strlen(arg->name);
		msh_specials_replace(str, arg->pseudo, i, len);
	}
}