#include "../includes/main.h"

void	msh_simple_execute(t_command *cmd, char **env)
{
	char	*s;
	int		ret;

	s = cmd->args[0];
	cmd->args[0] = msh_get_path(s, env);
	for( int i = 0; cmd->args[i]; i++)
	{
		printf("%s\n", cmd->args[i]);
	}
	(void) env;
	ret = fork();
	if (ret == 0)
	{
		if (execve(cmd->args[0], cmd->args, env) == -1)
		{
			perror(s);
			exit(1);
		}
	}
	waitpid(ret, NULL, 0);
	ft_strdel(&s);
}

int	msh_custom_redirect(t_redirect *red, t_specials specials)
{
	int			last;
	t_redirect	*tmp;

	tmp = NULL;
	if (red)
		tmp = red;
	while (tmp)
	{
		last = msh_open(tmp->file, specials);
		if (last == -1)
			perror(tmp->file);
		tmp = tmp->next;
	}
	return (last);
}

int	msh_buildins(t_command *cmd, int reg)
{
	int	is_buildin;

	is_buildin = 0;
	if (reg == 0 && ft_strnstr(cmd->args[0], "exit", 4) && ++is_buildin)
		msh_custom_exit(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "pwd", 3) && ++is_buildin)
		msh_custom_pwd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "echo", 4) && ++is_buildin)
		msh_custom_echo(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "env", 3) && ++is_buildin)
		msh_custom_env(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "cd", 2) && ++is_buildin)
		msh_custom_cd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 6) && ++is_buildin)
		msh_custom_export(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "unset", 5) && ++is_buildin)
		msh_custom_unset(cmd);
	return (is_buildin);
}

void	msh_cmd(char *line)
{
	t_command	*cmd;

	msh_parse(line);
	cmd = g_info.cur_cmd;
	while (cmd)
	{
		for( int i = 0; cmd->args[i]; i++)
		{
			printf("%s | ", cmd->args[i]);
		}
		printf("end of command\n");
		if (msh_buildins(cmd, 0))
			;
		else if (cmd->piped || cmd->input || cmd->out)
			msh_execute(cmd, g_info.env);
		else
			msh_simple_execute(cmd, g_info.env);

		cmd = cmd->next;
	}
}

void	msh_execute(t_command *cmd, char **env)
{
	int		ret;
	int		fd_cur[2];
	int		in_out_s[2];
	int		fdpipe[2];
	char	*s;
	
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	if (cmd->input)
		fd_cur[0] = msh_custom_redirect(cmd->input, cmd->specials);//open(cmd->input, O_RDONLY);
	else
		fd_cur[0] = dup(in_out_s[0]);
	//for
	dup2(fd_cur[0], STDIN_FILENO);
	close(fd_cur[0]);
	if (cmd->next == NULL) // if last command
	{
		if (cmd->out)
			fd_cur[1] = msh_custom_redirect(cmd->out, cmd->specials);//open(cmd->out, O_CREAT | O_TRUNC | O_RDWR);
		else
			fd_cur[1] = dup(in_out_s[1]);
	}
	else if (cmd->piped)
	{
		pipe(fdpipe);
		fd_cur[1] = fdpipe[1];
		fd_cur[0] = fdpipe[0];
	}
	dup2(fd_cur[1], STDOUT_FILENO);
	close(fd_cur[1]);
	if (cmd->piped)
	{
		ret = fork();
		if (ret == 0)
		{
			s = cmd->args[0];
			cmd->args[0] = msh_get_path(cmd->args[0], env);
			if (!msh_buildins(cmd, 1))
				if (execve(cmd->args[0], cmd->args, env) == -1)//(cmd->args[0], cmd->args, env) == -1)
				{
					perror(cmd->args[0]);
					exit(1);
				}
		}
	}
	// for end
	//restore in/out defaults
	dup2(in_out_s[0], 0);
	dup2(in_out_s[1], 1);
	close(in_out_s[0]);
	close(in_out_s[1]);
	msh_buildins(cmd, 1);

	int	status;
	if (!cmd->background && cmd->piped) //wait for last command
		waitpid(ret, &status, 0);
}



// void	msh_execute(t_command *cmd, char **env)
// {
// 	int		ret;
// 	int		fd_cur[2];
// 	int		in_out_s[2];
// 	int		fdpipe[2];
// 	char	*s;
	
// 	in_out_s[0] = dup(0);
// 	in_out_s[1] = dup(1);
// 	if (cmd->input)
// 		fd_cur[0] = msh_custom_redirect(cmd->input, cmd->specials);//open(cmd->input, O_RDONLY);
// 	else
// 		fd_cur[0] = dup(in_out_s[0]);
// 	//for
// 	dup2(fd_cur[0], STDIN_FILENO);
// 	close(fd_cur[0]);
// 	if (cmd->next == NULL) // if last command
// 	{
// 		if (cmd->out)
// 			fd_cur[1] = msh_custom_redirect(cmd->out, cmd->specials);//open(cmd->out, O_CREAT | O_TRUNC | O_RDWR);
// 		else
// 			fd_cur[1] = dup(in_out_s[1]);
// 	}
// 	else if (cmd->piped)
// 	{
// 		pipe(fdpipe);
// 		fd_cur[1] = fdpipe[1];
// 		fd_cur[0] = fdpipe[0];
// 	}
// 	dup2(fd_cur[1], STDOUT_FILENO);
// 	close(fd_cur[1]);
// 	if (cmd->piped)
// 	{
// 		ret = fork();
// 		if (ret == 0)
// 		{
// 			s = cmd->args[0];
// 			cmd->args[0] = msh_get_path(cmd->args[0], env);
// 			if (!msh_buildins(cmd, 1))
// 				if (execve(cmd->args[0], cmd->args, env) == -1)//(cmd->args[0], cmd->args, env) == -1)
// 				{
// 					perror(cmd->args[0]);
// 					exit(1);
// 				}
// 		}
// 	}
// 	// for end
// 	//restore in/out defaults
// 	dup2(in_out_s[0], 0);
// 	dup2(in_out_s[1], 1);
// 	close(in_out_s[0]);
// 	close(in_out_s[1]);
// 	msh_buildins(cmd, 1);

// 	int	status;
// 	if (!cmd->background && cmd->piped) //wait for last command
// 		waitpid(ret, &status, 0);
// }
