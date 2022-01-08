/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:25 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 20:21:39 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_wait_pid(int pid)
{
	int status;
	waitpid(pid, &status, 0);
	g_info.exit_code = WEXITSTATUS(status);
	//printf("%d", g_info.exit_code);
	if (status == 3)
		write(1, "Quit: 3\n", 9);
	if (status == 2)
		write(1, "\n", 1);
}

void	msh_pipes(t_command *cmd, int *fd_pipe)
{
	if ((cmd->prev && cmd->prev->piped))
	{
		if (!cmd->input)
			dup2(fd_pipe[0], 0);
		//else	dup2(fd_pipe[0], fd[0]);
		close(fd_pipe[0]);
	}
	if (cmd->piped && cmd->out == NULL)
	{
		if (pipe(fd_pipe) == -1)
			perror("Pipe");
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
	}
}

void	msh_func(t_command *cmd, int *fd_s, char **env)
{
	pid_t		pid;

	(void)env;
	if (!msh_buildins(cmd, 0))
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			close(fd_s[0]);
			close(fd_s[1]);
			if (!msh_buildins(cmd, 1))
				if (execve(cmd->args[0], cmd->args, env) == -1)
				 	msh_perror(cmd->args[0]);//ft_strrchr(cmd->args[0], '/') + 1);
			exit(g_info.exit_code);
		}
		msh_wait_pid(pid);
		signal(SIGINT, msh_sigint_handler);
	}
}

void	msh_execution(t_command *cmd, char **env, int *fd_pipe, int *fd_s)
{
	int		fd[2];
	
	if (cmd->redirects)
	{
		if (msh_custom_redirect(fd, cmd))
			return ;
		if (cmd->input)
		{
			dup2(fd[0], STDIN_FILENO);	// 0 указывает на файл с дескрпитором fd[0] 
			close(fd[0]);				// Закрываем fd[0] чтобы потомок не копировал его
										// в данный момент читать файл fd[0] можно только с фд 0
		}
		if (cmd->out)
		{
			dup2(fd[1], STDOUT_FILENO); // стандартный вывод закрывается и 1 начинает указывать на файл с дескриптором fd[1]
			close(fd[1]);				// Закрываем fd[1] чтобы потомок его не копировал 
										// в данный момент к записать файл fd[1] можно только STD_OUT (1)
		}
	}
	msh_pipes(cmd, fd_pipe);
	msh_func(cmd, fd_s, env);
}

int msh_preparings(t_command *cmd)
{
	msh_evaluate_all_tokens(cmd);
	cmd->build = msh_is_build(cmd->args[0]);
	for (int i = 0; i < cmd->num_args; i++)
	{
		printf("%s\n", cmd->args[i]);
	}
	if (msh_execution_validation(cmd) == -1)
		return (1) ;
	if (cmd->build != -1)
		msh_build_preparings(cmd);
	else if (!msh_make_path_relative(cmd))
		return (1) ;
	return (0);
}

void	msh_cmd(char *line)
{
	t_command	*cmd;
	int			in_out_s[2];
	int			fd_pipe[2];
	
	if (msh_parse(line) == -1)
		return ;
	if (msh_redirects_parse() == -1)
		return ;
	cmd = g_info.cur_cmd;
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	while (cmd)
	{
		if (msh_preparings(cmd))
			break ;
		msh_execution(cmd, g_info.env, fd_pipe, in_out_s);
		cmd = cmd->next;
		if ((cmd && !cmd->piped) || !cmd)
			dup2(in_out_s[1], 1);
	}
	close(in_out_s[1]);
	dup2(in_out_s[0], 0);
	close(in_out_s[0]);
}
