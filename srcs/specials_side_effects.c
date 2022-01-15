/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_side_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 19:00:47 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/**
 * @brief specify token if value exist
 * 
 * @return int if success returns 0 else return length of token name
 */
int	msh_specify_token(int *length, char *str, int sp)
{
	char		*name;
	char		*value[2];
	t_arg		*arg;
	t_command	*cmd;
	int 		result;
	
	cmd = msh_last_cmd();
	arg = NULL;
	ft_bzero(value, sizeof(char *) * 2);
	value[0] = g_info.func[sp](str, length);
	name = ft_strdup(value[0]);
	if (ft_strchr(value[0], '$') 
		&& sp != SLASH && sp != QUOTES && sp != CURL_BRACES)
		msh_evaluate_env_if_exist(value, g_info.env);
	if (value[0])
	{	
		arg = msh_create_token(name, value[0], g_info.num_token++, sp);
		msh_add_token(cmd, arg);
		return (0);
	}
	else
	{
		result = ft_strlen(name);
		ft_strdel(&name);
		return (result);
	}
}

void	msh_define_spaces(t_arg *arg, char *str, int *length, int specials)
{
	t_command	*cmd;
	int			add;
	char		*tmp;
	t_arg		*pre_arg;

	cmd = msh_last_cmd();
	add = 0;
	tmp = msh_get_prev_word(str, *length, ";|<> ");
	pre_arg = msh_get_token_value(cmd, tmp);
	if (pre_arg && msh_is_token(pre_arg->pseudo) && pre_arg->prev->is_prefix)
		arg->has_prefix = 1;
	else if (*length - 1 > -1 && str[*length - 1] != ' ')
		arg->has_prefix = 1;
	if (specials == 13 || specials == 14 || specials == 15)
		add += 2;
	if (*length + (int)ft_strlen(arg->name) + 1 <=\
		(int)ft_strlen(str) && str[*length + (int)ft_strlen(arg->name) + add] != ' ' &&\
			(int)ft_strlen(str) && str[*length + (int)ft_strlen(arg->name) + add] != '\0')
		arg->is_prefix = 1;
	ft_strdel(&tmp);
}

void	msh_common_side_effect(char **str, int *i, int sp)
{
	int		l;
	t_arg	*arg;
	int		len;

	len = 0;
	arg = NULL;
	if (sp == 13 || sp == 14 || sp == 15)
			len += 2;
	l = msh_specify_token(i, *str, sp);
	if (!l)
	{
		arg = msh_last_token();
		msh_define_spaces(arg, *str, i, sp);
		len += (int)ft_strlen(arg->name);
		msh_specials_replace(str, arg->pseudo, i, len);
	}
	else
		msh_specials_cut(str, i, l);
}

void	msh_curl_brace_side_effect()
{
	t_arg 	*last;
	char	*tmp;
	char	*new;

	last = msh_last_token();
	tmp = last->value;
	new = ft_strjoin("minishell ", tmp);
	last->value = new;
	ft_strdel(&tmp);
}

void	msh_cut_effect(char **str, int *i, int specials)
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
	if (specials == 25)
		msh_specials_cut(str, i, 1);
	else if (specials == 26)
	{
		msh_specials_cut(str, i, 1);
		(*i) += 2;
	}
	else
		msh_specials_cut(str, i, 2);
	(*i)--;
}

void	msh_side_effect(char **str, int *i, int sp)
{
	if (sp == -1)
		(*i)++;
	if (sp == 10 || sp == 11)
		msh_specials_cut(str, i, 2);
	if (sp == 13 || sp == 17 || sp == 14 || sp == 15 || sp == 18)
		msh_common_side_effect(str, i, sp);
	if (sp == 15)
		msh_curl_brace_side_effect();
	if (sp > 21)
		msh_cut_effect(str, &i[1], i[2]);
}
