/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:46 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/15 20:51:52 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_custom_pwd(t_command *cmd)
{
	char *str;

	(void)cmd;
	str = NULL;
	str = getcwd(NULL, 0);
	ft_putendl_fd(str, 1);
	ft_strdel(&str);
	msh_save_error_code(0);
	return (1);
}

int	msh_custom_env(t_command *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	while (g_info.env[i])
	{
		if (ft_index_of(g_info.env[i], '=', 0) != -1)
			ft_putendl_fd(g_info.env[i], 1);
		i++;
	}
	msh_save_error_code(0);
	return (1);
}

int	msh_custom_unset(t_command *cmd)
{
	int		i;
	int		res;
	char	**args;
	char	**tmp;
	int		length;

	i = 0;
	args = cmd->args;
	length = ft_str_count(g_info.env);
	while (args[i])
	{
		res = msh_env_exist(g_info.env, args[i]);
		if (res > -1)
		{
			ft_strdel(&g_info.env[res]);
			tmp = msh_concat_args(g_info.env, length);
			if (!tmp)
				return (msh_perror("malloc"));
			free(g_info.env);
			g_info.env = tmp;
			length = ft_str_count(g_info.env);
		}
		i++;
	}
	msh_save_error_code(0);
	return (1);
}

int	msh_buildins(t_command *cmd, int reg)
{
	int	is_buildin;

	is_buildin = 0;
	if (cmd->piped)
	 	return (0);
	if (reg == 0 && ft_strnstr(cmd->args[0], "exit", 5))
		msh_custom_exit(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "unset", 5))
		is_buildin = msh_custom_unset(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "cd", 3))
		is_buildin = msh_custom_cd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "pwd", 4))
		is_buildin = msh_custom_pwd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "echo", 5))
		is_buildin = msh_custom_echo(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "env", 4))
		is_buildin = msh_custom_env(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "export", 7)
		&& cmd->num_args > 1)
		is_buildin = msh_custom_export(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 7))
		is_buildin = msh_custom_export(cmd);
	return (is_buildin);
}

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
