#include "../includes/main.h"



void	msh_execute(t_command *cmd, char **env)
{
	int	fdin;
	int	tmpin;
	int	tmpout;
	int	fdpipe[2];
	
	tmpin = dup(0);
	tmpout = dup(1);
	if (cmd->input_file)
		fdin = open(cmd->input_file, O_RDONLY);
	else
		fdin = dup(tmpin);

	int	ret;
	int	fdout;
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	//for
	if (cmd->next == NULL)
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
		if (execve(msh_get_path(cmd->arguments[0], env), cmd->arguments, env) == -1)
		{
			perror(cmd->arguments[0]);
			exit(1);
		}
	}
	// for
	//restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	int	status;
	if (!cmd->background) //wait for last command
		waitpid(ret, &status, 0);
}
