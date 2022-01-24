/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 20:48:16 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_recursion_eval(int i, t_command *cmd, char **buff)
{
	t_arg	*an_tok;
	char	*tmp[2];

	an_tok = NULL;
	if (cmd->args[i] && msh_is_token(cmd->args[i]))
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
		|| (i < cmd->n_args && msh_is_token(cmd->args[i + 1])
			&& !msh_get_token_value(cmd, cmd->args[i + 1])->has_prefix))
		cmd->args[i] = tmp[0];
	else if (i < cmd->n_args)
		return (msh_recursion_eval(i + 1, cmd, &tmp[0]));
	return (i);
}

int	msh_token_mutations(t_arg *tok, t_command *cmd, int *i)
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
	if (tok->specials == WILDCARD)
	{
		msh_widlcard_mutations(cmd, tok, i);
		return (1);
	}
	else
		ft_strdel(&cmd->args[*i]);
	return (0);
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
	if (tok->is_prefix && tok->value)
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

	boo = ((!tok->has_prefix && !tok->is_prefix) || cmd->n_args == 1);
	if (boo)
	{
		if (tok->value)
			cmd->args[*i] = ft_strdup(tok->value);
		else
			cmd->args[*i] = NULL;
		(*i)++;
	}
	return (boo);
}

void	msh_evaluate_all_tokens(t_command *c)
{
	int		i;
	char	*tmp[4];
	t_arg	*tok;

	i = 0;
	ft_bzero(tmp, sizeof(char *) * 4);
	while (c->args && c->args[i])
	{
		tmp[0] = c->args[i];
		if (msh_is_token(c->args[i]))
		{
			tok = msh_get_token_value(c, c->args[i]);
			if (msh_token_mutations(tok, c, &i) == 1)
				continue ;
			if (!tmp[0] && ++i)
				continue ;
			if (msh_no_prefix(tok, c, &i))
				continue ;
			msh_procedure(&i, tok, c, tmp);
			msh_replace_null_arg(c);
		}
		else
			i++;
	}
}
