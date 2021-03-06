/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:45 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 17:48:23 by dwulfe           ###   ########.fr       */
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

void	msh_push_redirect(t_redirect **current, char *value,
	t_specials specials)
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

void	msh_add_token(t_command *cmd, t_arg *arg)
{
	if (cmd && !cmd->token)
	{
		cmd->token = arg;
		cmd->token->prev = cmd->token;
	}
	else
	{
		cmd->token->prev->next = arg;
		arg->prev = cmd->token->prev;
		cmd->token->prev = arg;
	}
}
