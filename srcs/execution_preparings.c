/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 19:59:54 by dwulfe           ###   ########.fr       */
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

void	msh_token_convertations(t_arg *tok)
{
	if (tok->specials == SLASH)
	{
		tok->value[0] = tok->value[1];
		tok->value[1] = '\0';
	}
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

/*
	int		i;
	char	*tmp[4];
	t_arg	*tok;
	t_arg	*next_tok;
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
			next_tok = msh_get_token_value(cmd, cmd->args[i + 1]);
			if (!tok)
			{
				i++;
				continue;
			}
			if (tok->has_prefix && tok->is_prefix && !next_tok)
			{
				tmp[2] = ft_strjoin(cmd->args[i - 1], tok->value);
				tmp[1] = ft_strjoin(tmp[2], cmd->args[i + 1]);
				ft_strdel(&tmp[2]);
				ft_strdel(&cmd->args[i]);

			}
			else if (tok->has_prefix && tmp[1])
			{
				tmp[2] = ft_strjoin(tmp[1], tok->value);
				ft_swap_strs(&tmp[2], &tmp[1]);
				ft_strdel(&tmp[2]);
			}
			else if (tok->is_prefix && !tmp[1]) // first
				tmp[1] = tok->value;
			if (tok->has_prefix && !tok->is_prefix)// stop concatination
			{
				ft_strdel(&cmd->args[i]);
				cmd->args[i] = tmp[1];
				tmp[1] = NULL;
			}
			else if (!tok->has_prefix && !tok->is_prefix) 
			{
				ft_strdel(&cmd->args[i]);
				cmd->args[i] = tok->value;
				continue;

			}
			else
				ft_strdel(&cmd->args[i]);
			msh_replace_null_arg(cmd);
		}
		else if (tmp[1])
		{
			tmp[2] = ft_strjoin(tmp[1], cmd->args[i]);
			ft_swap_strs(&tmp[2], &tmp[1]);
			ft_strdel(&tmp[2]);
			ft_strdel(&tmp[0]);
			cmd->args[i] = tmp[1];
			tmp[1] = NULL;
		}
		else
			i++;
	}
*/
/*
			tok = msh_get_token_value(cmd, cmd->args[i]);
			if (tok->has_prefix)
			{
				tmp[2] = ft_strjoin(tmp[1], tok->value);
				ft_swap_strs(&tmp[2], &tmp[1]);
				ft_strdel(&tmp[2]);
			}
			else if (tok->is_prefix && !tmp[1])
				tmp[i] = tok->value;
			else if (tok->is_prefix && tmp[1])
			{
				cmd->args[cmd->num_args] = tmp[1];
				tmp[1] = tok->value;
			}
			else
			{
				tmp[2] = cmd->args[i];
				ft_strdel(&tmp[2]);
				cmd->args[i] = tok->value;
			}
			ft_strdel(&tmp[0]);
			// t = msh_concat_args(cmd->args, cmd->num_args);
			// ft_arrstr_del(cmd->args, cmd->num_args);
			// cmd->args = t;
			// cmd->num_args = ft_str_count(cmd->args);
*/

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
	else //if (ft_strncmp(tmp, cmd->args[0], ft_strlen(tmp)) != 0)
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}
