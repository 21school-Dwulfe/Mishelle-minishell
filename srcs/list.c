/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:45 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/06 17:12:38 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_add_command(t_command **cur_cmd, char **value)
{
	t_command	*tmp;

	if (cur_cmd && *cur_cmd)
	{
		tmp = msh_create_command(value);
		(*cur_cmd)->prev->next = tmp;
		tmp->prev = (*cur_cmd)->prev;
		(*cur_cmd)->prev = tmp;
	}
}

void	msh_push_command(t_command **cur_cmd, char **value)
{
	t_command	*tmp;

	tmp = msh_create_command(value);
	if (cur_cmd && *cur_cmd)
	{
		(*cur_cmd)->prev->next = tmp;
		tmp->prev = (*cur_cmd)->prev;
		(*cur_cmd)->prev = tmp;
	}
	else
	{
		*cur_cmd = tmp;
		(*cur_cmd)->prev = tmp;
	}
}

void	msh_add_redirect(t_redirect **current, char *value, t_specials specials)
{
	t_redirect	*tmp;

	tmp = msh_create_redirect(value, specials);
	if (current && *current)
	{
		(*current)->prev->next = tmp;
		tmp->prev = (*current)->prev;
		(*current)->prev = tmp;
	}
	else
	{
		*current = tmp;
		(*current)->prev = tmp;
	}
}

// t_arg	*msh_add_token(t_command *cmd, char *name, int order, int specials)
// {
// 	t_arg	*tmp;

// 	if (cmd && !cmd->args_token)
// 	{
// 		tmp = msh_create_token(name, NULL, order, specials);
// 		cmd->args_token = tmp;
// 		cmd->args_token->prev = cmd->args_token;
// 	}
// 	else
// 	{
// 		tmp = msh_create_token(name, NULL, order, specials);
// 		cmd->args_token->prev->next = tmp;
// 		tmp->prev = cmd->args_token->prev;
// 		cmd->args_token->prev = tmp;
// 	}
// 	return (tmp);
// }

void	msh_add_token(t_command *cmd, t_arg *arg)
{
	if (cmd && !cmd->args_token)
	{
		cmd->args_token = arg;
		cmd->args_token->prev = cmd->args_token;
	}
	else
	{
		cmd->args_token->prev->next = arg;
		arg->prev = cmd->args_token->prev;
		cmd->args_token->prev = arg;
	}
}