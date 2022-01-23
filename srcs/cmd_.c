/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:46 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/23 18:43:39 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_buildins_s(t_command *cmd)
{
	int	result;

	result = 0;
	if (ft_strnstr(cmd->args[0], "exit", 4))
		msh_custom_exit(cmd);
	else if (ft_strnstr(cmd->args[0], "unset", 5))
		result = msh_custom_unset(cmd);
	else if (ft_strnstr(cmd->args[0], "cd", 2))
		result = msh_custom_cd(cmd);
	else if (ft_strnstr(cmd->args[0], "pwd", 3))
		result = msh_custom_pwd(cmd);
	else if (ft_strnstr(cmd->args[0], "echo", 4))
		result = msh_custom_echo(cmd);
	else if (ft_strnstr(cmd->args[0], "env", 3))
		result = msh_custom_env(cmd);
	else if (ft_strnstr(cmd->args[0], "export", 6)
		&& cmd->num_args > 1)
		result = msh_custom_export(cmd);
	else if (ft_strnstr(cmd->args[0], "export", 6))
		result = msh_custom_export(cmd);
	return (result);
}
