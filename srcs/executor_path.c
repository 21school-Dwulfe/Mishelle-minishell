/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:26 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/23 18:05:25 by dwulfe           ###   ########.fr       */
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
	{
		msh_wait_pid(0);
		if (g_info.exit_code > 0 && !cmd->piped
			&& cmd->specials == DOUBLE_AMP)
		exec_result = 1;
	}
	if (cmd->specials == DOUBLE_AMP && g_info.exit_code > 0)
		exec_result = 1;
	if (cmd->specials == DOUBLE_PIPE && g_info.exit_code == 0)
		exec_result = 2;
	if (cmd->specials == DOUBLE_PIPE && g_info.exit_code > 0)
		exec_result = 0;
	return (exec_result);
}

int	msh_make_path_relative(t_command *cmd)
{
	int		res;
	char	*tmp;

	res = 0;
	tmp = NULL;
	if (!cmd->args)
		return (0);
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if (!tmp && msh_get_env_by_key(g_info.env, "PATH"))
	{
		msh_error_bash("command not found", cmd->args[0], 127);
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

void	msh_heredoc_input(char *name)
{
	int		i[3];
	char	*ptr[3];
	int		fd;

	i[0] = ft_strlen(name);
	i[1] = 1;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	while (i[1])
	{
		msh_readline(">", &ptr[0]);
		ptr[2] = ft_strnstr(ptr[0], name, i[0]);
		if (ptr[2])
		{
			i[1] = 0;
			ft_strdel(&ptr[0]);
			break ;
		}
		else
		{
			write(fd, ptr[0], ft_strlen(ptr[0]));
			write(fd, "\n", 1);
			ft_strdel(&ptr[0]);
		}
	}
	close(fd);
}
