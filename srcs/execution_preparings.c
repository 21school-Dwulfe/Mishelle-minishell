/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/07 19:56:35 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void msh_evaluate_all_tokens(t_command *cmd)
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
			if (tok->has_prefix)
				tmp[1] = ft_strjoin(cmd->args[i - 1], tok->value);
			else if (tok->is_prefix)
				tmp[1] = tok->value;
			else
			{
				tmp[2] = cmd->args[i];
				ft_strdel(&tmp[2]);
				cmd->args[i] = tok->value;
			}
		}
		else if (tmp[1])
		{
			tmp[2] = cmd->args[i];
			tmp[3] = ft_strjoin(tmp[1], tmp[2]);
			ft_strdel(&cmd->args[i]);
			ft_strdel(&tmp[2]);
			cmd->args[i] = tmp[3];
		}
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
	else if (ft_strncmp(tmp, cmd->args[0], ft_strlen(tmp)) != 0)
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}
