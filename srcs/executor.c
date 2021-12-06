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

void	msh_custom_redirect(t_command *cmd)
{
	// t_command *tmp;
	// int			i;
	(void)cmd;
	// i = 0;
	// if (cmd->input_file)
	// 	tmp = cmd;
	// while (cmd->input_file)
	// {
	// 	if (msh_open(cmd->input_file, cmd->specials) == -1)
	// 		perror(cmd->input_file);
		
	// 	i++;
	// }
}

void	msh_custom_r_redirect(t_command *cmd, char *str)
{
	(void)cmd;
	(void)str;
	// if (!ft_strcmp(g_info.current_command->args[0], "<"))
	// {
		
	// }
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
		 
		// if (ft_strnstr(cmd->args[0], "exit", 4))
		// 	msh_custom_exit(cmd);
		// else if (ft_strnstr(cmd->args[0], "pwd", 3))
		// 	msh_custom_pwd(cmd);
		// else if (ft_strnstr(cmd->args[0], "echo", 4))
		// 	msh_custom_echo(cmd);
		// else if (ft_strnstr(cmd->args[0], "env", 3))
		// 	msh_custom_env(cmd);
		// else if (ft_strnstr(cmd->args[0], "cd", 2))
		// 	msh_custom_cd(cmd);
		// else if (ft_strnstr(cmd->args[0], "export", 6))
		// 	msh_custom_export(cmd);
		// else if (ft_strnstr(cmd->args[0], "unset", 5))
		// 	msh_custom_unset(cmd);
		// else if (ft_strnstr(cmd->args[0], ">", 2))
		// 	msh_custom_redirect(cmd);
		// else if (ft_strnstr(cmd->args[0], "<", 2))
		// 	msh_custom_r_redirect(cmd);
		// else
		// {
		// 	if (cmd->piped)
		// 		msh_execute(cmd, g_info.env);
		// 	else
		// 		msh_simple_execute(cmd, g_info.env);
		// }
		cmd = cmd->next;
	}
}


// void	msh_execute(t_command *cmd, char **env)
// {
// 	int	fdin;
// 	int	tmpin;
// 	int	tmpout;
// 	int	fdpipe[2];
// 	int	ret;
// 	int	fdout;
// 	char *s;
	
// 	tmpin = dup(0);
// 	tmpout = dup(1);
// 	if (cmd->input_file)
// 		fdin = open(cmd->input_file, O_RDONLY);
// 	else
// 		fdin = dup(tmpin);

// 	//for
// 	dup2(fdin, STDIN_FILENO);
// 	close(fdin);
// 	if (cmd->next == NULL) // if  last command
// 	{
// 		if (cmd->out_file)
// 			fdout = open(cmd->out_file, O_CREAT | O_TRUNC | O_RDWR);
// 		else
// 			fdout = dup(tmpout);
// 	}
// 	else
// 	{
// 		pipe(fdpipe);
// 		fdout = fdpipe[1];
// 		fdin = fdpipe[0];
// 	}
// 	dup2(fdout, STDOUT_FILENO);
// 	close(fdout);

// 	ret = fork();
// 	if (ret == 0)
// 	{
// 		s = cmd->args[0];
// 		cmd->args[0] = msh_get_path(cmd->args[0], env);
// 		//ft_strdel(s);
// 		// for( int i = 0; i < 1; i++)
// 		// {
// 		// 	printf("%s\n", cmd->args[i]);
// 		// }
// 		if (execve(cmd->args[0], cmd->args, env) == -1)//(cmd->args[0], cmd->args, env) == -1)
// 		{
// 			perror(cmd->args[0]);
// 			exit(1);
// 		}
// 	}// for end
// 	//restore in/out defaults
// 	dup2(tmpin, 0);
// 	dup2(tmpout, 1);
// 	close(tmpin);
// 	close(tmpout);
// 	int	status;
// 	if (!cmd->background) //wait for last command
// 		waitpid(ret, &status, 0);
// }
