#include "../includes/main.h"
#include <errno.h>

int msh_custom_redirect(int *fd_arr, t_command *cmd)
{
	int			fd_index;
	t_redirect	*tmp;

	fd_index = 0;
	tmp = NULL;
	if (cmd)
		tmp = cmd->redirects;
	while (tmp)
	{
		if (tmp->specials == 5 || tmp->specials == 7)
		{
			if (cmd->input)
				close(fd_arr[0]);
			cmd->input = tmp;
			fd_index = 0;
		}
		if (tmp->specials == 4 || tmp->specials == 6)
		{
			if (cmd->out)
				close(fd_arr[1]);
			cmd->out = tmp;
			fd_index = 1;
		}
		fd_arr[fd_index] = msh_open(tmp->file, tmp->specials);
		if (fd_arr[fd_index] == -1)
		{
			perror(tmp->file);
			return (1);
		}
		tmp = tmp->next;
	}
	return(0);
}

int msh_buildins(t_command *cmd, int reg)
{
	int	is_buildin;

	is_buildin = 0;
	if (reg == 0 && ft_strnstr(cmd->args[0], "exit", 4))
		msh_custom_exit(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "unset", 5))
		is_buildin = msh_custom_unset(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "cd", 2))
		is_buildin = msh_custom_cd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "pwd", 3))
		is_buildin = msh_custom_pwd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "echo", 4))
		is_buildin = msh_custom_echo(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "env", 3))
		is_buildin = msh_custom_env(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "export", 6)
		&& cmd->num_args > 1)
		is_buildin = msh_custom_export(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 6))
		is_buildin = msh_custom_export(cmd);
	return (is_buildin);
}

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
				{
					perror(cmd->args[0]);
					exit(1);
				}
			exit(g_info.exit_code);
		}
		msh_wait_pid(pid);
		signal(SIGINT, msh_sigint_handler);
	}
}

void	msh_execution(t_command *cmd, char **env, int *fd_pipe, int *fd_s)
{
	int			fd[2];
	
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

int	msh_is_build(char *cmd)
{
	int i;
	int len;

	i = 0;
	
	while (i < 7)
	{
		len = ft_strlen(g_info.f[i]);
		if (!ft_strncmp(cmd, g_info.f[i], len))
			return (i + 1);
		i++;
	}
	return (0);
}

char	**msh_replace_and_copy(char **args, char *new, int index)
{
	int	i;
	int len;
	char **arr;
	
	arr = NULL;
	i = 0;
	len = ft_str_count(args);
	arr = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (i == index)
		{
			arr[i] = new;
			ft_strdel(&args[index]);
		}
		else
		{
			arr[i] = args[i];
			args[i] = NULL;
		}
		i++;
	}
	arr[i] = 0;
	free(args);
	return (arr);
}

void	msh_cmd(char *line)
{
	t_command	*cmd;
	int			in_out_s[2];
	int			fd_pipe[2];
	char		*tmp[2];

	ft_bzero(tmp, sizeof(char *) * 2);
	msh_parse(line);
	cmd = g_info.cur_cmd;
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	while (cmd)
	{
		tmp[0] = cmd->args[0];
		cmd->build = msh_is_build(cmd->args[0]);
		if (!cmd->build)
		{
			tmp[1] = msh_get_path(tmp[0], g_info.env);
			if(!tmp[1])
				break ;
			cmd->args = msh_replace_and_copy(cmd->args, tmp[1], 0);
		}
		msh_execution(cmd, g_info.env, fd_pipe, in_out_s);
		cmd = cmd->next;
		if ((cmd && !cmd->piped) || !cmd)
			dup2(in_out_s[1], 1);
	}
	close(in_out_s[1]);
	dup2(in_out_s[0], 0);
	close(in_out_s[0]);
}
