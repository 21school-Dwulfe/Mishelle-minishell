/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:06:05 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_evaluate_all_tokens(t_command *cmd)
{
	int	i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		tmp = cmd->args[i];
		if (msh_is_token(cmd->args[i]))
		{
			msh_exchange_token_value(cmd, i);
		}
			
		i++;
	}
}

int	msh_make_path_relative(t_command *cmd)
{
	int res;
	char	*tmp;

	res = 1;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if(!tmp)
	{
		msh_error_bash("command not found", cmd->args[0], 127);
		res = 0;
	}
	else if(ft_strncmp(tmp, cmd->args[0] , ft_strlen(tmp)) != 0)
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}