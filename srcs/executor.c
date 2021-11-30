#include "../includes/main.h"

void	msh_cmd(char *line)
{
	int			i;
	t_command	*cmd;

	i = 0;
	msh_parse(line);
	cmd = g_info.current_command;
	while (cmd)
	{
		msh_evaluate_env_call_if_exist(cmd, g_info.env);
		if (ft_strnstr(cmd->args[0], "exit", 4))
			msh_custom_exit(cmd);
		else if (ft_strnstr(cmd->args[0], "pwd", 3))
			msh_custom_pwd(cmd);
		else if (ft_strnstr(cmd->args[0], "echo", 4))
			msh_custom_echo(cmd);
		else if (ft_strnstr(cmd->args[0], "env", 3))
			msh_custom_env(cmd);
		else if (ft_strnstr(cmd->args[0], "cd", 2))
			msh_custom_cd(cmd);
		else if (ft_strnstr(cmd->args[0], "export", 6))
			msh_custom_export(cmd);
		else if (ft_strnstr(cmd->args[0], "unset", 5))
			msh_custom_unset(cmd);
		else
			msh_execute(cmd, g_info.env);
		cmd = cmd->next;
	}

	// редирект если есть 
}
void ft_zhivchich()
{
	write(1, "hren", 4);
}

/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 */
void	msh_execute(t_command *cmd, char **env)
{
	int	fdin;
	int	tmpin;
	int	tmpout;
	int	fdpipe[2];
	int	ret;
	int	fdout;
	
	tmpin = dup(0);
	tmpout = dup(1);
	if (cmd->input_file)
		fdin = open(cmd->input_file, O_RDONLY);
	else
		fdin = dup(tmpin);

	//for
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	if (1) // if not last command
	{
		if (cmd->out_file)
			fdout = open(cmd->out_file, O_CREAT | O_TRUNC | O_RDWR);
		else
			fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		fdout = fdpipe[1];
		fdin = fdpipe[0];
	}
	dup2(fdout, STDOUT_FILENO);
	close(fdout);

	ret = fork();
	if (ret == 0)
	{
		ft_zhivchich();
		if (execve(msh_get_path(cmd->args[0], env), cmd->args, env) == -1)
		{
			perror(cmd->args[0]);
			exit(1);
		}
	}// for end
	//restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	int	status;
	if (!cmd->background) //wait for last command
		waitpid(ret, &status, 0);
}
