#include "../includes/main.h"

int	msh_custom_redirect(int *fd_arr, t_command *cmd)
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
			printf("%s\n", tmp->file);
			perror(tmp->file);
			return (1);
		}
		tmp = tmp->next;
	}
	return(0);
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
	int		i;
	int		len;
	// char	*ptr;
	// char	*tmp;

	i = 0;
	while (i < 7)
	{
		len = ft_strlen(g_info.f[i]);
		if (!ft_strncmp(cmd, g_info.f[i], len))
			return (i + 1);
		// ptr = ft_strnstr(cmd, "minishell", ft_strlen(g_info.f[i]));
		// if (ptr)
		// {
		// 	tmp = ft_strndup_se(cmd, ft_strlen(cmd) - 10, 0);
		// 	if (ft_strncmp());
		// }
		i++;
	}
	return (-1);
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
	arr[i] = NULL;
	return (arr);
}

void	msh_evaluate_all_tokens(t_command *cmd)
{
	int 		i;

	i = 0;
	while (cmd->args[i])
	{
		if (msh_is_token(cmd->args[i]))
			msh_exchange_token_value(cmd, i);
		i++;
	}
}

void	msh_shlvl(char **env)
{
	int		index;
	char	*shlvl;
	char	*new_shlvl[2];
	
	index = msh_env_exist(env, "SHLVL");
	shlvl = msh_get_env_by_key(env, "SHLVL");
	new_shlvl[0] = ft_itoa(ft_atoi(shlvl + 1));
	new_shlvl[1] = ft_strjoin("SHLVL", new_shlvl[0]);
	ft_strdel(&new_shlvl[0]);
	msh_modify_env_var(&env[index], new_shlvl[1]);
}

void	msh_shell_bin(char **env, char *path)
{
	int		index;
	int		new_len;
	char	*new_shell;
	
	index = msh_env_exist(env, "SHELL");
	new_len = ft_strlen(path) + 16;
	new_shell = ft_calloc(new_len, sizeof(char));
	new_shell = ft_strncat(new_shell, "SHELL=", new_len);
	new_shell = ft_strncat(new_shell, path, new_len);
	new_shell[6 + ft_strlen(path)] = '/';
	new_shell = ft_strncat(new_shell, "minishell", new_len);
	msh_modify_env_var(&env[index], new_shell);
}

void	msh_shell_prepare(t_command *cmd)
{
	if (cmd->build == 7)
	{
		cmd->args[0] = ft_strjoin(g_info.pwd, g_info.f[7]);
		ft_strdel(&cmd->args[0]);
		msh_shlvl(g_info.env);
		msh_shell_bin(g_info.env, g_info.pwd);
	}
}

int	msh_make_path_relative(t_command *cmd)
{
	int		res;
	char	*tmp;

	res = 1;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if(!tmp)
	{
		msh_error_bash("command not found", cmd->args[0], 127);
		res = 0;
	}
	else if(ft_strncmp(tmp, cmd->args[0] , ft_strlen(tmp)) != 0)
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
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
		msh_evaluate_all_tokens(cmd);
		cmd->build = msh_is_build(cmd->args[0]);
		if (cmd->build != -1)
			msh_shell_prepare(cmd);
		else if (!msh_make_path_relative(cmd))
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
