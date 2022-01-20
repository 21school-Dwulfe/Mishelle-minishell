/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_side_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/20 22:36:43 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// void	msh_heredoc_key_value(t_arg *tok)
// {
// 	int		i;
// 	char	tmp;
		
// 	i = 2;
// 	while (tok->value[i] && tok->value[i] == ' ')
// 		i++;
// 	tmp = tok->value;
// 	tok->value = ft_strdup("");
// 	ft_strdel(&tok->name);
// 	tok->name = ft_strdup(tmp + i);
// 	ft_strdel(&tmp);
// }
char	*msh_heredoc_value_to_name(char *value)
{
	int		i;
	char	*tmp;
		
	i = 2;
	while (value[i] && value[i] == ' ')
		i++;
	tmp = value;
	value = ft_strdup(tmp + i);
	ft_strdel(&tmp);
	return (value);
}

/**
 * @brief specify token if value exist
 * 
 * @param length current index position in line
 * @param str incoming line with commands 
 * @param sp special sign code
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
	if (sp == RD_REDIRECT)
	{
		result = ft_strlen(value[0]);
		name = msh_heredoc_value_to_name(value[0]);
		msh_add_redirect(&cmd->redirects, name, sp);
		msh_heredoc_input(name);
		return (result);
	}
	// if (sp == WILDCARD)
	// {// если файл будет с редиректом то либо менять старую логику редиректов либо убрать строку в токен wildcard 
		
	// }
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
	if (!l && sp != RD_REDIRECT)
	{
		arg = msh_last_token();
		msh_define_spaces(arg, *str, i, sp);
		len += (int)ft_strlen(arg->name);
		msh_specials_replace(str, arg->pseudo, i, len);
	}
	else
	{
		msh_specials_cut(str, i, l);
		if (sp == RD_REDIRECT && *i - 1 > -1)
			(*i)--;
	}
}

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
			*src =  msh_concat_str(str, len[1], NULL);
			ft_strdel(&str);
			str = *src;
			i -= len[0];
		}
		i++;
	}
}

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
	if (str && *i - 1 >= 0)
		(*i)--;
}

void	msh_side_effect(char **str, int *i, int *sp)
{
	if (*sp == -1)
		(*i)++;
	if (*sp == 10 || *sp == 11)
		msh_specials_cut(str, i, 2);
	if (*sp == 13 || *sp == 17 || *sp == 14 || *sp == 15 || *sp == 18 || *sp == 19
		|| *sp == 7)
		msh_common_side_effect(str, i, *sp);
	if (*sp == 15)
		msh_specials_replace(str, "minishell ", i, 1);
	if (*sp > 21)
		msh_cut_effect(str, i, *sp);
	if (ft_strlen(*str) == 0)
		*sp = -1;
}
