/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/17 17:00:06 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int msh_recursion_eval(int i, t_command *cmd, char **buff)
{
	t_arg 	*an_tok;
	char 	*tmp[2];

	an_tok = NULL;
	if (msh_is_token(cmd->args[i]))
	{
		an_tok = msh_get_token_value(cmd, cmd->args[i]);
		if (an_tok)
			tmp[1] = an_tok->value;
		else
			tmp[1] = "";
	}
	else
		tmp[1] = cmd->args[i];
	tmp[0] = ft_strjoin(*buff, tmp[1]);
	ft_strdel(buff);
	ft_strdel(&cmd->args[i]);
	if (cmd->args[i + 1] == NULL || (an_tok && !an_tok->is_prefix))
		cmd->args[i] = tmp[0];
	else if (an_tok && an_tok->is_prefix)
		return(msh_recursion_eval(i + 1, cmd, &tmp[0]));
	return (i);
}

void msh_heredoc_input(t_arg *tok)
{
	int 	i;
	int		value_len;
	int		tok_name_len;
	int		recursion;
	char	*ptr;
	
	i = 0;
	value_len = 0;
	recursion = 1;
	tok_name_len = ft_strlen(tok->name);
	while (recursion)
	{
		msh_input_call(&tok->value, 0);
		while (1)
		{
			ptr = ft_strnstr(tok->value + i, tok->name, tok_name_len);
			if (!ptr)
			{
				recursion = 0;
				break ;
			}
			if (i - 1 == value_len)
			{
				recursion = 1;
				break ;
			}
			i++;
		}
	}
}

void	msh_token_convertations(t_arg *tok)
{
	if (tok->specials == SLASH)
	{
		tok->value[0] = tok->value[1];
		tok->value[1] = '\0';
	}
	if (tok->specials == D_REDIRECT)
		msh_heredoc_input(tok);
}

void msh_evaluate_all_tokens(t_command *cmd)
{
	int		i;
	char	*tmp[4];
	t_arg	*tok;
	char	**mirror;

	i = 0;
	ft_bzero(tmp, sizeof(char *) * 4);
	mirror = cmd->args;
	(void)mirror;
	while (cmd->args[i])
	{
		tmp[0] = cmd->args[i];
		if (msh_is_token(cmd->args[i]))
		{
			tok = msh_get_token_value(cmd, cmd->args[i]);
			msh_token_convertations(tok);
			ft_strdel(&cmd->args[i]);
			if (!tmp[0])
			{
				i++;
				continue;
			}
			if (!tok->has_prefix && !tok->is_prefix)
			{
				cmd->args[i] = ft_strdup(tok->value);
				i++;
				continue;
			}
			if (tok->has_prefix)
			{
				if (msh_is_token(cmd->args[i - 1]))
					tmp[1] = msh_get_token_value(cmd, cmd->args[i - 1])->value;
				else
					tmp[1] = cmd->args[i - 1];
				tmp[2] = ft_strjoin(tmp[1], tok->value);
				ft_strdel(&cmd->args[i - 1]);
			}
			if (tok->is_prefix)
			{
				if (!tmp[2])
					tmp[2] = ft_strdup(tok->value);
				msh_recursion_eval(i + 1, cmd, &tmp[2]);
			}
			else
				cmd->args[i] = tmp[2];
			msh_replace_null_arg(cmd);
		}
		else
			i++;
	}
}

int msh_make_path_relative(t_command *cmd)
{
	int res;
	char *tmp;

	res = 1;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if (!tmp)
	{
		msh_error_bash("command not found", cmd->args[0], 127);
		res = 0;
	}
	else
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}
