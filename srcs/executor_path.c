/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:26 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 16:00:28 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_splited(char *cmd_name, char **tmp, int *i)
{
	char	**splited;

	splited = ft_split(tmp[0], ':');
	while (tmp[0] && splited[i[0]])
	{
		tmp[1] = ft_strjoin(splited[i[0]], "/");
		tmp[2] = ft_strjoin(tmp[1], cmd_name);
		ft_strdel(&tmp[1]);
		if (access(tmp[2], F_OK) == 0)
			break ;
		else
			ft_strdel(&tmp[2]);
		i[0]++;
	}
	ft_arrstr_del(splited, ft_str_count(splited));
}

char	*msh_get_path(char *cmd_name, char **env)
{
	int			res;
	int			i[2];
	char		*tmp[4];

	ft_bzero(i, sizeof(int) * 2);
	ft_bzero(tmp, sizeof(char *) * 4);
	if (!ft_strncmp(cmd_name, "", 2))
		return (NULL);
	res = access(cmd_name, F_OK);
	if (res == -1 && ++i[1])
	{
		tmp[0] = msh_get_env_by_key(env, "PATH");
		msh_splited(cmd_name, tmp, i);
	}
	else
		return (ft_strdup(cmd_name));
	return (tmp[2]);
}

int	msh_d_amp_d_pipe(t_command *cmd)
{
	int	exec_result;

	exec_result = 0;
	if ((cmd->build == 8 || cmd->build == -1)
		&& (cmd->specials == DOUBLE_AMP || cmd->specials == DOUBLE_PIPE))
		msh_wait_pid(0);
	if (cmd->specials == DOUBLE_AMP && g_info.exit_code > 0)
		exec_result = 1;
	if (cmd->specials == DOUBLE_PIPE && g_info.exit_code == 0)
		exec_result = 2;
	if (cmd->specials == DOUBLE_PIPE && g_info.exit_code > 0)
		exec_result = 0;
	return (exec_result);
}

// if (!cmd->num_args && cmd->redirects)
// 		return (1);
// if (!cmd->args)
// 	return (msh_error_bash("command not found", cmd->args[0], 127));
int	msh_make_path_relative(t_command *cmd)
{
	int		res;
	char	*tmp;

	res = 0;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if (!tmp && (msh_get_env_by_key(g_info.env, "PATH") \
		|| !ft_strncmp(cmd->args[0], "", 2)))
	{
		msh_error_bash(" command not found", cmd->args[0], 127);
		res = 1;
	}
	else if (!tmp && !msh_get_env_by_key(g_info.env, "PATH"))
		return (msh_error_bash("No such file or directory", cmd->args[0], 127));
	else
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}
