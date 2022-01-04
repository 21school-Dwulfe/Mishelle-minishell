/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:57 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:08:58 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_shlvl(char **env)
{
	int		index;
	char	*shlvl;
	char	*new_shlvl[2];
	
	index = msh_env_exist(env, "SHLVL");
	shlvl = msh_get_env_by_key(env, "SHLVL");
	new_shlvl[0] = ft_itoa(ft_atoi(shlvl + 1));
	new_shlvl[1] = ft_strjoin("SHLVL", new_shlvl[0]);
	ft_strdel(&new_shlvl[0]);
	msh_modify_env_var(&env[index], new_shlvl[1]);
}

void	msh_shell_bin(char **env, char *path)
{
	int		index;
	int		new_len;
	char	*new_shell;
	
	index = msh_env_exist(env, "SHELL");
	new_len = ft_strlen(path) + 16;
	new_shell = ft_calloc(new_len, sizeof(char));
	new_shell = ft_strncat(new_shell, "SHELL=", new_len);
	new_shell = ft_strncat(new_shell, path, new_len);
	new_shell[6 + ft_strlen(path)] = '/';
	new_shell = ft_strncat(new_shell, "minishell", new_len);
	msh_modify_env_var(&env[index], new_shell);
}

void	msh_build_preparings(t_command *cmd)
{
	if (cmd->build == 7)
	{
		cmd->args[0] = ft_strjoin(g_info.pwd, g_info.f[7]);
		ft_strdel(&cmd->args[0]);
		msh_shlvl(g_info.env);
		msh_shell_bin(g_info.env, g_info.pwd);
	}
	else
	{
		
	}
	
}