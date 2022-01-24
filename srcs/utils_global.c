/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:19:15 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 23:43:57 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_init_global_cmd(void)
{
	t_command	*cmd;

	cmd = msh_create_command((void *)0);
	cmd->prev = cmd;
	g_info.cur_cmd = cmd;
}

void	msh_clear_tokens(t_command *cmd)
{
	t_arg		*tmp_arg;

	tmp_arg = cmd->token;
	while (tmp_arg)
	{
		cmd->token = cmd->token->next;
		ft_strdel(&tmp_arg->name);
		ft_strdel(&tmp_arg->pseudo);
		ft_strdel(&tmp_arg->value);
		free(tmp_arg);
		tmp_arg = cmd->token;
	}
}

t_command	*msh_last_cmd(void)
{
	return (g_info.cur_cmd->prev);
}

t_redirect	*msh_last_redirect(t_command *cmd)
{
	return (cmd->redirects->prev);
}

void	msh_struct_clear(void)
{
	t_command	*cmd;
	t_redirect	*tmp_red;

	cmd = g_info.cur_cmd;
	g_info.num_token = 0;
	g_info.num_of_commands = 0;
	while (cmd)
	{
		if (cmd->args)
			ft_arrstr_del(cmd->args, ft_str_count(cmd->args));
		msh_clear_tokens(cmd);
		tmp_red = cmd->redirects;
		while (tmp_red)
		{
			cmd->redirects = cmd->redirects->next;
			ft_strdel(&tmp_red->file);
			free(tmp_red);
			tmp_red = cmd->redirects;
		}
		cmd = cmd->next;
		free(g_info.cur_cmd);
		g_info.cur_cmd = NULL;
		g_info.cur_cmd = cmd;
	}
}
