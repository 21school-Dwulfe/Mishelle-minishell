// #include "../minishell.h"

// // void	msh_wait_pid(int pid)
// // {
// // 	int status;
// // 	waitpid(pid, &status, 0);
// // 	g_info.exit_code = WEXITSTATUS(status);
// // 	printf("%d", g_info.exit_code);
// // 	if (status == 3)
// // 		write(1, "Quit: 3\n", 9);
// // 	if (status == 2)
// // 		write(1, "\n", 1);
// // }

// // void	msh_pipes(t_command *cmd, int *fd_pipe, int	*fd_s)
// // {
// // 	(void)fd_s;
// // 	if ((cmd->prev && cmd->prev->piped))
// // 	{
// // 		if (!cmd->input)
// // 			dup2(fd_pipe[0], 0);
// // 		//else	dup2(fd_pipe[0], fd[0]);
// // 		close(fd_pipe[0]);
// // 	}
// // 	if (cmd->piped && cmd->out == NULL)
// // 	{
// // 	//	dup2(fd_s[1], 1);
// // 		if (pipe(fd_pipe) == -1)
// // 			perror("Pipe");
// // 		dup2(fd_pipe[1], 1);
// // 		close(fd_pipe[1]);
// // 	}
// // }

// // void	msh_func(t_command *cmd, int *fd_s, char **env)
// // {
// // //	pid_t		pid;

// // 	(void)env;
// // 	(void)fd_s;
// // 	//signal(SIGINT, SIG_IGN);
// // 	// pid = fork();
// // 	// if (pid == 0)
// // 	// {
// // 		// signal(SIGINT, SIG_DFL);
// // 		// signal(SIGQUIT, SIG_DFL);
// // 		// close(fd_s[0]);
// // 		// close(fd_s[1]);
// // 		if (!msh_buildins(cmd, 1))
// // 			if (execve(cmd->args[0], cmd->args, env) == -1)
// // 				msh_perror(cmd->args[0]);//ft_strrchr(cmd->args[0], '/') + 1);
// // 		exit(errno);
// // //	}
// // }

// // void	msh_execution(t_command *cmd, char **env)
// // {
// // 	int		fd[2];

// // 	if (cmd->redirects)
// // 	{
// // 		if (msh_custom_redirect(fd, cmd))
// // 			return ;
// // 		if (cmd->input)
// // 		{
// // 			dup2(fd[0], STDIN_FILENO);	// 0 указывает на файл с дескрпитором fd[0]
// // 			close(fd[0]);				// Закрываем fd[0] чтобы потомок не копировал его
// // 										// в данный момент читать файл fd[0] можно только с фд 0
// // 		}
// // 		if (cmd->out)
// // 		{
// // 			dup2(fd[1], STDOUT_FILENO); // стандартный вывод закрывается и 1 начинает указывать на файл с дескриптором fd[1]
// // 			close(fd[1]);				// Закрываем fd[1] чтобы потомок его не копировал 
// // 										// в данный момент к записать файл fd[1] можно только STD_OUT (1)
// // 		}
// // 	}
// // 	msh_pipes(cmd, fd_pipe, fd_s);
// // 	msh_func(cmd, fd_s, env);
// // }

// // int msh_preparings(t_command *cmd)
// // {
// // 	msh_evaluate_all_tokens(cmd);
// // 	cmd->build = msh_is_build(cmd->args[0]);
// // 	for (int i = 0; i < cmd->num_args; i++)
// // 	{
// // 		printf("%s\n", cmd->args[i]);
// // 	}
// // 	if (msh_execution_validation(cmd) == -1)
// // 		return (1) ;
// // 	if (cmd->build != -1)
// // 		msh_build_preparings(cmd);
// // 	else if (!msh_make_path_relative(cmd))
// // 		return (1) ;
// // 	return (0);
// // }

// // void	msh_wait_pid(int pid)
// // {
// // 	int status;
// // 	waitpid(pid, &status, 0);
// // 	g_info.exit_code = WEXITSTATUS(status);
// // 	printf("%d", g_info.exit_code);
// // 	if (status == 3)
// // 		write(1, "Quit: 3\n", 9);
// // 	if (status == 2)
// // 		write(1, "\n", 1);
// // }

// void	msh_pip(t_command *cmd)
// {
// 	if ((cmd->prev && cmd->prev->piped))
// 	{
// 		if (!cmd->input)
// 		{
// 			dup2(cmd->prev->std->in, 0);
// 			printf("copy fd_pipe %d to 0 %d close\n",cmd->prev->std->in, 0);
// 		}
// 		close(cmd->prev->fd->in);
// 	}
// 	if (cmd->piped && cmd->out == NULL)
// 	{
// 		dup2(cmd->std->out, 1);
// 		printf("copy fd_pipe %d to 0 %d close\n",cmd->std->out, 1);

// 		close(cmd->std->out);
// 	}
// }

// int **msh_pipe_allocate(t_command *cmd)
// {
// 	int		i;
// 	int		tmp_pipe[2];

// 	i = 0;
// 	while (i < g_info.num_of_commands - 1)
// 	{
// 		if (cmd->piped)
// 		{
// 			cmd->std = malloc(typeof(t_fd));
// 			if (!cmd->std)
// 			{
// 				msh_error_bash("Malloc fd", cmd->args[0], 12);
// 				exit(errno);
// 			}

// 			if (pipe(tmp_pipe) == -1)
// 			{
// 				// g_info.exit_code = errno;
// 				// while (i--)
// 				// {
// 				// 	close(cmd->std->in[0]);
// 				// 	close(cmd->std->out[1]);
// 				// }
// 				msh_error_bash("Pipe error", cmd->args[0], errno);
// 				exit(g_info.exit_code);
// 			}
// 			cmd->std->in = tmp_pipe[0];
// 			cmd->std->out = tmp_pipe[1];
// 		}
// 		cmd = cmd->next;
// 		i++;
// 	}
// 	return (fd_pipe);
// }

// void	msh_close_fd(int count, int **fd_pipe, t_command *cmd)
// {
// 	// int i;

// 	// i = 0;
// 	// (void)cmd;
// 	// while (i < count)
// 	// {
// 	// 	close(fd_pipe[i][0]);
// 	// 	close(fd_pipe[i][1]);
// 	// 	free(fd_pipe[i]);
// 	// 	i++;
// 	// }
// 	// free(fd_pipe);
// 	// while (cmd)
// 	// {
// 	// 	if (cmd->input)
// 	// 		close(cmd->input);
// 	// 	if (cmd->out)
// 	// 		close(cmd->out);
// 	// 	cmd = cmd->next;
// 	// }
	
// }

// void	msh_pipex_loop(t_command *cmd, char **env)
// {
// 	pid_t		*pid;
// //	t_command	*cmd_copy;
// 	int			i;
// 	int			**fd_pipe;

// 	i = 0;
// //	cmd_copy = cmd;
// 	fd_pipe = msh_pipe_allocate(cmd);
// 	pid = malloc(sizeof(pid_t) * g_info.num_of_commands);
// 	while (i < g_info.num_of_commands)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == 0)
// 		{
// 			ft_putstr_fd("child", 1);
// 			signal(SIGINT, msh_child_sig);
// 			signal(SIGQUIT, msh_child_sig);
// 			if (msh_preparings(cmd))
// 				break ;
// 			msh_redirects_fd(cmd);
// 			msh_pip(cmd, &fd_pipe[i]);
// 			if (!msh_buildins_s(cmd))
// 				if (execve(cmd->args[0], cmd->args, env) == -1)
// 				msh_perror(cmd->args[0]);
// 			exit(g_info.exit_code);
// 		}
// 		cmd = cmd->next;
// 		i++;
// 	}
// //	msh_close_fd(i, fd_pipe, cmd_copy);
// 	while (i-- > 0)
// 	{
// 		msh_wait_pid(-1);
// 	}
// }