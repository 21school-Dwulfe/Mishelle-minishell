/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 22:18:36 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_recursion_eval(int i, t_command *cmd, char **buff)
{
	t_arg	*an_tok;
	char	*tmp[2];

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
	if (cmd->args[i + 1] == NULL || (an_tok && !an_tok->is_prefix)
		|| (msh_is_token(cmd->args[i + 1])
			&& !msh_get_token_value(cmd, cmd->args[i + 1])->has_prefix))
		cmd->args[i] = tmp[0];
	else
		return (msh_recursion_eval(i + 1, cmd, &tmp[0]));
	return (i);
}

void	msh_token_mutations(t_arg *tok)
{
	if (tok->specials == SLASH)
	{
		tok->value[0] = tok->value[1];
		tok->value[1] = '\0';
	}
	if (ft_strncmp(tok->name, "$?", 3) == 0)
	{
		ft_strdel(&tok->value);
		tok->value = ft_itoa(msh_read_error_code());
	}
}

void	msh_procedure(int *i, t_arg *tok, t_command *cmd, char **tmp)
{
	if (tok->has_prefix)
	{
		if (msh_is_token(cmd->args[*i - 1]))
			tmp[1] = msh_get_token_value(cmd, cmd->args[*i - 1])->value;
		else
			tmp[1] = cmd->args[*i - 1];
		tmp[2] = ft_strjoin(tmp[1], tok->value);
		ft_strdel(&cmd->args[*i - 1]);
	}
	if (tok->is_prefix)
	{
		if (!tmp[2])
			tmp[2] = ft_strdup(tok->value);
		msh_recursion_eval(*i + 1, cmd, &tmp[2]);
	}
	else
		cmd->args[*i] = tmp[2];
}

int	msh_no_prefix(t_arg *tok, t_command *cmd, int *i)
{
	int	boo;

	boo = ((!tok->has_prefix && !tok->is_prefix) || cmd->num_args == 1);
	if (boo)
	{
		cmd->args[*i] = ft_strdup(tok->value);
		(*i)++;
	}
	return (boo);
}

void	msh_evaluate_all_tokens(t_command *cmd)
{
	int		i;
	char	*tmp[4];
	t_arg	*tok;

	i = 0;
	ft_bzero(tmp, sizeof(char *) * 4);
	while (cmd->args[i])
	{
		tmp[0] = cmd->args[i];
		if (msh_is_token(cmd->args[i]))
		{
			tok = msh_get_token_value(cmd, cmd->args[i]);
			msh_token_mutations(tok);
			ft_strdel(&cmd->args[i]);
			if (!tmp[0] && ++i)
				continue ;
			if (msh_no_prefix(tok, cmd, &i))
				continue ;
			msh_procedure(&i, tok, cmd, tmp);
			msh_replace_null_arg(cmd);
		}
		else
			i++;
	}
}
