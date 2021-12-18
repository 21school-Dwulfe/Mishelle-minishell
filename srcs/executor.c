#include "../includes/main.h"

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
		is_buildin = msh_custom_exit(cmd);
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
	else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 6))
		is_buildin = msh_custom_export(cmd);
	return (is_buildin);
}
	// is_buildin = 0;
	// if (reg == 0 && ft_strnstr(cmd->args[0], "exit", 4))
	// 	is_buildin = msh_custom_exit(cmd);
	// else if (reg == 0 && ft_strnstr(cmd->args[0], "unset", 5))
	// 	is_buildin = msh_custom_unset(cmd);
	// else if (reg == 0 && ft_strnstr(cmd->args[0], "cd", 2))
	// 	is_buildin = msh_custom_cd(cmd);
	// else if (reg == 1 && ft_strnstr(cmd->args[0], "pwd", 3))
	// 	is_buildin = msh_custom_pwd(cmd);
	// else if (reg == 1 && ft_strnstr(cmd->args[0], "echo", 4))
	// 	is_buildin = msh_custom_echo(cmd);
	// else if (reg == 1 && ft_strnstr(cmd->args[0], "env", 3))
	// 	is_buildin = msh_custom_env(cmd);
	// else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 6)
	// 	&& cmd->num_args > 1 && !(--cmd->piped))
	// 	is_buildin = msh_custom_export(cmd);
	// return (is_buildin);

void	msh_execution(t_command *cmd, char **env, int *fd_pipe, int *fd_s)
{
	int			fd[2];
	pid_t		ret;

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
	
	ret = fork();
	if (ret == 0)
	{
		close(fd_s[0]);
		close(fd_s[1]);
		if (!msh_buildins(cmd, 1)) 
			if (execve(cmd->args[0], cmd->args, env) == -1)
			{
				perror(cmd->args[0]);
				exit(1);
			}
	}
	waitpid(ret, NULL, 0);
}

int	msh_is_build(char *cmd)
{
	int i;
	int len;

	i = 0;
	
	while (i < 7)
	{
		len = ft_strlen(g_info.f[i]);
		if (ft_strncmp(cmd, g_info.f[i], len))
			return (i);
		i++;
	}
	return (0);
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
			ft_strdel(&tmp[0]);
			cmd->args[0] = tmp[1];
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
