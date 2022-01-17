#include "../../includes/main.h"

void	msh_wait_pid(int pid)
{
	int status;
	int	west;

	waitpid(pid, &status, 0);
	west = WEXITSTATUS(status);
	msh_save_error_code(west);
//	printf("%d %d", g_info.exit_code, WEXITSTATUS(status));
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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, msh_pipex_sig);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, msh_child_sig);
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
}

int msh_preparings(t_command *cmd)
{
	int build;

	msh_evaluate_all_tokens(cmd);
	if (msh_execution_validation(cmd) == 1)
		return (1);
	build = msh_is_build(cmd->args[0]);
	if (build == -1 || build == 8)
		if (!msh_make_path_relative(cmd))
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
	if (!cmd->piped)
		result = msh_buildins(cmd, 0);
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
	if (g_info.exit_code > 0)
	{
		if (cmd->piped && cmd->specials > 9
			&& cmd->specials < 12)
				msh_wait_pid(-1);
		exec_result = 1;
	}
	if (cmd->specials == DOUBLE_PIPE && g_info.exit_code == 0)
		exec_result = 2;
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
		if (msh_preparings(cmd))
			break ;
		msh_redirects_fd(cmd);
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
