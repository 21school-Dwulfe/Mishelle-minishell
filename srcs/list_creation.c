/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:05:11 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 18:18:11 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_command	*msh_create_command(char **dstr)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->args = dstr;
	cmd->background = 0;
	cmd->input = NULL;
	cmd->out = NULL;
	cmd->err = NULL;
	cmd->piped = 0;
	cmd->token = NULL;
	cmd->build = 0;
	if (dstr)
		cmd->n_args = ft_str_count(dstr);
	else
		cmd->n_args = 0;
	cmd->prev = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redirect	*msh_create_redirect(char *filepath, int specials)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	redirect->file = filepath;
	redirect->specials = specials;
	redirect->next = NULL;
	redirect->prev = NULL;
	return (redirect);
}

t_arg	*msh_create_token(char *name, char *value, int order, int specials)
{
	t_arg	*args_token;

	args_token = malloc(sizeof(t_arg));
	args_token->next = NULL;
	args_token->prev = NULL;
	args_token->name = name;
	args_token->value = value;
	args_token->is_prefix = 0;
	args_token->has_prefix = 0;
	args_token->pseudo = msh_generate_tokens(specials, order);
	args_token->specials = specials;
	args_token->order = order;
	return (args_token);
}
