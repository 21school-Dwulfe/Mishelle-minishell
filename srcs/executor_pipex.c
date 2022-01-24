/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:01:31 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 20:49:31 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_wait_pid(int pid)
{
	int			status;
	int			west;
	int			child_term;
	static int	filter;

	waitpid(pid, &status, 0);
	west = WEXITSTATUS(status);
	child_term = WTERMSIG(status);
	if (!filter++)
	{
		if (child_term == 3)
			write(2, "Quit: 3\n", 8);
		if (child_term == 2)
			write(2, "\n", 2);
	}
	if (filter == g_info.num_of_commands)
		filter = 0;
	msh_save_error_code(west);
}

int	msh_pipes(t_command *cmd, int *fd_pipe)
{
	int	pipe_status;

	pipe_status = 1;
	if ((cmd->prev && cmd->prev->next != NULL && cmd->prev->piped))
	{
		if (!cmd->input)
			dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
	}
	if (cmd->piped && cmd->out == NULL)
	{
		pipe_status = pipe(fd_pipe);
		if (pipe_status == -1)
		{
			perror("Pipe");
			return (-1);
		}
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
	}
	return (!pipe_status);
}

void	msh_func(t_command *cmd, int *fd_s, char **env, int *fd_pipe)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->build == 8)
			msh_sigignore();
		else
			signal(SIGQUIT, msh_child_sig);
		if (cmd->prev->next != NULL && cmd->prev->piped)
			close(fd_pipe[1]);
		if (cmd->piped)
			close(fd_pipe[0]);
		close(fd_s[1]);
		close(fd_s[0]);
		if (!msh_buildins_s(cmd))
		{
			if (execve(cmd->args[0], cmd->args, env) == -1)
				msh_perror(cmd->args[0]);
			exit(errno);
		}
		exit(g_info.exit_code);
	}
	msh_sigignore();
}

int	msh_preparings(t_command *cmd)
{
	int	build;

	msh_evaluate_all_tokens(cmd);
	if (ft_str_count(cmd->args) == 0 && cmd->token)
		cmd->args[0] = ft_strdup("");
	build = msh_is_build(cmd->args[0]);
	if (build == -1 || build == 8)
	{
		if (cmd->args && cmd->args[0] == NULL)
			return (1);
		if (msh_make_path_relative(cmd))
			return (1);
		if (msh_first_arg_validation(cmd) == 1)
			return (1);
	}
	return (0);
}

int	msh_buildin_excutor(t_command *cmd)
{
	int		result;
	int		len;
	char	*tmp;

	result = 0;
	cmd->build = msh_is_build(cmd->args[0]);
	if (cmd->build == 8)
	{
		tmp = cmd->args[0];
		len = ft_strlen(g_info.pwd) + ft_strlen(g_info.f[7]) + 1;
		cmd->args[0] = ft_calloc(len, sizeof (char));
		ft_strncat(cmd->args[0], g_info.pwd, len);
		cmd->args[0][ft_strlen(cmd->args[0])] = '/';
		ft_strncat(cmd->args[0], g_info.f[7], len);
		ft_strdel(&tmp);
	}
	if (!cmd->piped && cmd->build != -1)
		result = msh_buildins_s(cmd);
	return (result);
}
