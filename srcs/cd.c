/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:39 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:04:41 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_cd_validation(t_command *cmd, char *new)
{
	(void)new;
	if (cmd->num_args > 1)
	{
		if (cmd->args[1] && cmd->args[1][0] == '.'
			&& cmd->args[1][1] == '\0')
			return (1);
		DIR *dir = opendir(new);
		if (dir == NULL)
			return (msh_error_bash("No such file or directory", new, 127));
		else
			if (closedir(dir))
				msh_perror(new);
	}
	return (0);
}

int	msh_custom_cd(t_command *cmd)
{
	char	*str;
	char	*env_value[5];
	int		old_cur[3];

	str = NULL;
	(void)cmd;
	ft_bzero(old_cur, sizeof(int) * 3);
	ft_bzero(env_value, sizeof(char *) * 5);
	old_cur[0] = msh_env_exist(g_info.env, "OLDPWD");
	old_cur[1] = msh_env_exist(g_info.env, "PWD");
	env_value[0] = msh_get_env_by_key(g_info.env, "OLDPWD");
	env_value[1] = msh_get_env_by_key(g_info.env, "PWD");
	if (cmd->num_args == 1)
		env_value[2] = msh_get_env_by_key(g_info.env, "HOME");
	else if (!env_value[0] && cmd->num_args > 1 && !ft_strncmp(cmd->args[1], "-", 2))
	{
		write(1, "Mishelle: cd: OLDPWD not set\n", 30);
		return (g_info.exit_code = 1);
	}
	else if (!ft_strncmp(cmd->args[1], "-", 2))
	{
		env_value[2] = env_value[0];
		old_cur[2] = 1;
	}
	else if (cmd->args[1][0] == '~' && cmd->args[1][1] == '\0')
		env_value[2] = msh_get_env_by_key(g_info.env, "HOME");
	else if (cmd->args[1][0] == '~' && cmd->args[1][1] == '/')
	{
		env_value[3] = msh_get_env_by_key(g_info.env, "HOME");
		env_value[2] = ft_strndup_se(env_value[3], ft_strlen(env_value[3]) + ft_strlen(cmd->args[1] + 1), 0);
		ft_strncat(env_value[2], cmd->args[1] + 1, ft_strlen(env_value[3]) + ft_strlen(cmd->args[1] + 1) + 2);
	}
	else
		env_value[2] = cmd->args[1];
	if (msh_cd_validation(cmd, env_value[2]))
		return (1);
	if (old_cur[0])
		msh_modify_env_var(&g_info.env[old_cur[0]], getcwd(str, sizeof(str)* 512));
	else
	{
		env_value[3] = ft_strjoin("OLDPWD=", str);
		g_info.env = msh_create_env_var(env_value[3]);
	}
	if(chdir(env_value[2]) == -1)
		msh_perror("cd");
	env_value[4] = getcwd(str, sizeof(str)* 512);
	if (old_cur[2])
		ft_putendl_fd(env_value[4], 1);
	msh_modify_env_var(&g_info.env[old_cur[1]], env_value[4]);
	return (1);
}
