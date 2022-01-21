/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:01:31 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/20 22:08:24 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_wait_pid(int pid)
{
	int status;
	int	west;
	int	child_term;
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
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
		}
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int msh_preparings(t_command *cmd)
{
	int build;

	if (!cmd)
		return (1);
	msh_evaluate_all_tokens(cmd);
	if (msh_first_arg_validation(cmd) == 1)
		return (1);
	build = msh_is_build(cmd->args[0]);
	if (build == -1 || build == 8)
		if (msh_make_path_relative(cmd))
			return (1);
	return (0);
}

int	msh_buildin_excutor(t_command *cmd)
{
	int		result;
	int 	len;
	char	*tmp;

	result = 0;
	cmd->build = msh_is_build(cmd->args[0]);
	if (cmd->build == 8)
	{
		tmp = cmd->args[0];
		len = ft_strlen(g_info.pwd)	+ ft_strlen(g_info.f[7]) + 1;
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

/**
 * @brief Check if we need not to continue all execution or miss next command
 * 
 * @param cmd Current command
 * @return int | 0=Nothing | 1=Error in exc DOUBLE_AMP | 2=Error in exc DOUBLE_PIPE
 */
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

int    msh_executor(t_command *cmd, char **env, int *in_out_s)
{
	int		fd_pipe[2];
	int		counter;
	int		status;

	counter = 0;
	while (cmd)
	{
		status = msh_preparings(cmd);
		status = msh_redirects_fd(cmd);
		if (status == 1)
			break ;
		else if (status == 2)
		{
			cmd = cmd->next;
			continue;
		}
		if (msh_buildin_excutor(cmd) == 0)
		{
			if (msh_pipes(cmd, fd_pipe) > -1)
				counter++;
			else
				return (-1);
			msh_func(cmd, in_out_s, env, fd_pipe);
		}
		status = msh_d_amp_d_pipe(cmd);
		if (status == 1)
			break ;
		else if (status == 2)
			cmd = cmd->next;
		cmd = cmd->next;
		if ((cmd && !cmd->piped) || !cmd)
			dup2(in_out_s[1], 1);
	}
	return (counter);
}
