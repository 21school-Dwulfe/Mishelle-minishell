#include "minishell.h"

// int	msh_wait_pid(int pid)
// {
// 	int status;

// 	waitpid(pid, &status, 0);
// 	g_info.exit_code = WEXITSTATUS(status);
// 	printf("%d", g_info.exit_code);
// 	if (status == 3)
// 		write(1, "Quit: 3\n", 9);
// 	if (status == 2)
// 		write(1, "\n", 1);
// 	return (g_info.exit_code);
// }

// void	msh_pipe_input(t_command *cmd, int *fd_pipe)
// {
// 	if ((cmd->prev && cmd->prev->piped))
// 	{
// 		if (!cmd->input)
// 			dup2(fd_pipe[0], 0);
// 		close(fd_pipe[0]);
// 	}
// }

// void	msh_pipe_output(t_command *cmd, int *fd_pipe)
// {
// 	if (cmd->piped && cmd->out == NULL)
// 	{
// 		if (pipe(fd_pipe) == -1)
// 			perror("Pipe");
// 		dup2(fd_pipe[1], 1);
// 		close(fd_pipe[1]);
// 	}
// }

// void	msh_func(t_command *cmd, int *fd_s, char **env)
// {
	
// 	(void)env;
// 	(void)fd_s;
// 	if (!msh_buildins(cmd, 0))
// 	{
// 		//signal(SIGINT, SIG_IGN);
// 		//signal(SIGINT, msh_sigint_handler);
		
		
// 			// signal(SIGINT, SIG_DFL);
// 			// signal(SIGQUIT, SIG_DFL);
// 			// close(fd_s[0]);
// 			// close(fd_s[1]);
// 			if (!msh_buildins(cmd, 1))
// 				if (execve(cmd->args[0], cmd->args, env) == -1)
// 				 	msh_perror(cmd->args[0]);//ft_strrchr(cmd->args[0], '/') + 1);
// 			exit(g_info.exit_code);
// //		msh_wait_pid(pid);
// 		//signal(SIGINT, msh_sigint_handler);
// 	}
// }

// void	msh_pipes(t_command *cmd, int *fd_pipe)
// {
// 	if ((cmd->prev && cmd->prev->piped))
// 	{
// 		if (!cmd->input)
// 			dup2(fd_pipe[0], 0);
// 		//else	dup2(fd_pipe[0], fd[0]);
// 		close(fd_pipe[0]);
// 	}
// 	if (cmd->piped && cmd->out == NULL)
// 	{
// 		if (pipe(fd_pipe) == -1)
// 			perror("Pipe");
// 		dup2(fd_pipe[1], 1);
// 		close(fd_pipe[1]);
// 	}
// }

// void	msh_after_execution_effect(int *in_out_s)
// {
// 	// if ((cmd && !cmd->piped) || !cmd)
// 	//	dup2(in_out_s[1], 1);
// 	close(in_out_s[1]);
// 	dup2(in_out_s[0], 0);
// 	close(in_out_s[0]);
	
// }

// int msh_preparings(t_command *cmd)
// {
// 	msh_evaluate_all_tokens(cmd);
// 	cmd->build = msh_is_build(cmd->args[0]);
// 	// for (int i = 0; i < cmd->num_args; i++)
// 	// {
// 	// 	printf("%s\n", cmd->args[i]);
// 	// }
// 	if (msh_execution_validation(cmd) == -1)
// 		return (1) ;
// 	if (cmd->build != -1)
// 		msh_build_preparings(cmd);
// 	else if (!msh_make_path_relative(cmd))
// 		return (1) ;
// 	return (0);
// }

// void	msh_do_it(t_command *cmd, char **env, int *fd_pipe, int *fd_s)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (msh_preparings(cmd))
// 		exit(g_info.exit_code);
// //	dup2(fd_s[1], 1);
// 	msh_redirects_fd(cmd);
// 	msh_func(cmd, fd_s, env);
// 	msh_wait_pid(pid);
// 	msh_after_execution_effect(fd_pipe);
// }


// void	msh_cmd(char *line)
// {
// 	t_command	*cmd;
// 	int			in_out_s[2];
// 	int			fd_pipe[2];
// 	int			pid;

// 	if (msh_parse(line) == -1)
// 		return ;
// 	if (msh_redirects_parse() == -1)
// 		return ;
// 	cmd = g_info.cur_cmd;
// 	signal(SIGINT, SIG_IGN);
// 	fd_pipe[0] = 0;
// 	fd_pipe[1] = 1;
// 	in_out_s[0] = dup(0);
// 	in_out_s[1] = dup(1);
// 	// if (cmd->piped && cmd->out == NULL)
// 	// {
// 	// 	signal(SIGINT, SIG_DFL);
// 	// 	signal(SIGQUIT, SIG_DFL);
// 	// 	pid = fork();
// 	// 	if (pid == 0)
// 	// 		msh_execution(cmd, env, fd_pipe, fd_s);
// 	// }
// 	pid = fork();
// 	if (pid == 0)
// 		msh_execution(cmd, g_info.env, fd_pipe, in_out_s);
// 	msh_wait_pid(pid);
// 	signal(SIGINT, msh_sigint_handler);
// }

void    msh_pipex_two_step(t_command *cmd, char **env)
{
	// int		fd_pipe[2];
	// int		pid[2];

	(void)cmd;
	(void)env;
	// cmd = g_info.cur_cmd;
	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	// while (cmd)
	// {
	// 	if (cmd->piped && cmd->out == NULL)
	// 	{
	// 		msh_pipes(cmd, fd_pipe);
	// 		pid[0] = fork();
	// 		if (pid == 0)
	// 			msh_do_it(cmd->, env, fd_pipe);
	// 	}
	// 	pid[1] = fork();
	// 	if (pid[1] == 0)
	// 		msh_do_it(cmd, g_info.env, fd_pipe);
	// 	msh_wait_pid(pid[0]);
	// 	msh_wait_pid(pid[1]);
	// 	cmd = cmd->next->next;
	// }
	// signal(SIGINT, msh_sigint_handler);
}