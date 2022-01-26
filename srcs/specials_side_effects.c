/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_side_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:12 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_convert(t_command *cmd, char *value, int sp, char *name)
{
	t_arg		*arg;
	int			len;

	if (sp >= 4 && sp <= 7)
	{
		len = ft_strlen(name);
		msh_convert_to_redirect(cmd, value, sp);
		msh_cut_quotes(&msh_last_redirect(cmd)->file, 0, len);
		ft_strdel(&name);
		ft_strdel(&value);
		if (sp == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			msh_heredoc_input(msh_last_redirect(cmd)->file);
			signal(SIGINT, msh_sigint_handler);
		}
		return (len);
	}
	if (sp == TILDA)
		msh_convert_tilda(&value, name);
	arg = msh_create_token(ft_strdup(name), value, g_info.num_token++, sp);
	msh_add_token(cmd, arg);
	len = ft_strlen(name);
	ft_strdel(&name);
	return (len);
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
	t_command	*cmd;

	cmd = msh_last_cmd();
	ft_bzero(value, sizeof(char *) * 2);
	value[0] = g_info.func[sp](str, length);
	name = ft_strdup(value[0]);
	if (ft_strchr(value[0], '$')
		&& sp != SLASH && sp != QUOTES && sp != CURL_BRACES)
		msh_evaluate_env_if_exist(value, g_info.env);
	if (sp == WILDCARD)
	{
		ft_memset(value[0], '\0', ft_strlen(value[0]));
		msh_wildcard(msh_get_env_by_key(g_info.env, "PWD"), &value[0]);
	}
	return (msh_convert(cmd, value[0], sp, name));
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
	if (*length + (int)ft_strlen(arg->name) + 1 <= \
		(int)ft_strlen(str) && str[*length
			+ (int)ft_strlen(arg->name) + add] != ' ' && \
				(int)ft_strlen(str) && str[*length
			+ (int)ft_strlen(arg->name) + add] != '\0')
		arg->is_prefix = 1;
	ft_strdel(&tmp);
}

void	msh_common_side_effect(char **str, int *i, int sp)
{
	t_arg	*arg;
	int		len;

	len = 0;
	arg = NULL;
	if (sp == 13 || sp == 14 || sp == 15)
		len += 2;
	len += msh_specify_token(i, *str, sp);
	if (sp != SLASH && sp != HEREDOC && sp != REDIRECT
		&& sp != R_REDIRECT && sp != D_REDIRECT)
	{
		arg = msh_last_token();
		msh_define_spaces(arg, *str, i, sp);
		msh_specials_replace(str, arg->pseudo, i, len);
	}
	else
	{
		msh_specials_cut(str, i, len);
		if ((sp == HEREDOC || sp == DOLLAR) && *i - 1 > -1)
			(*i)--;
	}
}
