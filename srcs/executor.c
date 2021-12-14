#include "../includes/main.h"

void	msh_simple_execute(t_command *cmd, char *path, char **env)
{
	pid_t		ret;
//	int			status;
	//char *sss[] = {"/usr/bin/ls", "-ls", NULL};
	//int			fd_pipe[2];
	//char 		*str;

	// if (pipe(fd_pipe) < 0)
	// 	perror("Error");
//	s = cmd->args[0];
	ft_strdel(&cmd->args[0]);
	cmd->args[0] = path;
	ret = fork();
	if (ret == 0)
	{
		// dup2(fd_pipe[1], STDOUT_FILENO);
		// close(fd_pipe[0]);
		// close(fd_pipe[1]);
		// write(1, "cattttt",8);
	//	printf("%s\n",cmd->args[0]);
		if (execve(cmd->args[0], cmd->args, env) == -1)
		{
		
			perror(cmd->args[0]);
			exit(1);
		}
	
	}
	
	// else
	// 	perror("simple fork");
	// dup2(fd_pipe[0], STDIN_FILENO);
	// str = msh_read_fd(0);
	// str[ft_strlen(str) - 1] = '\0';
	// close(fd_pipe[0]);
	// close(fd_pipe[1]);
	waitpid(ret, NULL, 0);
	//WEXITSTATUS(status);
	//printf("%d\n", status);
}

void msh_custom_redirect(int *fd_arr, t_command *cmd)
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
			// if (cmd->input)
			// 	close(fd_arr[0]);
			cmd->input = tmp;
			fd_index = 0;
		}
		if (tmp->specials == 4 || tmp->specials == 6)
		{
			// if (cmd->out)
			// 	close(fd_arr[1]);
			cmd->out = tmp;
			fd_index = 1; 
		}
		fd_arr[fd_index] = msh_open(tmp->file, tmp->specials);
		// if (fd_index == 0 && tmp->next == NULL)
		// {
		// 	dup2(fd_arr[fd_index], 0);
		// 	close(fd_arr[fd_index]);
		// 	msh_simple_execute(cmd, msh_get_path(cmd->args[0], g_info.env) , g_info.env);
		// 	break;
		// }
		if (fd_arr[fd_index] == -1)
		{
			perror(tmp->file);
			break ;
		}
		tmp = tmp->next;
	}
}

int	msh_buildins(t_command *cmd, int reg)
{
	int	is_buildin;

	is_buildin = 0;
	if (reg == 0 && ft_strnstr(cmd->args[0], "exit", 4))
		is_buildin = msh_custom_exit(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "pwd", 3))
		is_buildin = msh_custom_pwd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "echo", 4))
		is_buildin = msh_custom_echo(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "env", 3))
		is_buildin = msh_custom_env(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "cd", 2))
		is_buildin = msh_custom_cd(cmd);
	else if (reg == 1 && ft_strnstr(cmd->args[0], "export", 6))
		is_buildin = msh_custom_export(cmd);
	else if (reg == 0 && ft_strnstr(cmd->args[0], "unset", 5))
		is_buildin = msh_custom_unset(cmd);
	return (is_buildin);
}

void	msh_cmd(char *line)
{
	msh_parse(line);
	msh_execute(g_info.cur_cmd, g_info.env);
}

void	msh_execute(t_command *cmd_s, char **env)
{
	t_command	*cmd;
	int			ret;
	int			fd_cur[2];
	int			in_out_s[2];
	int			fd_pipe[2];
	char		*path;
	char		*s;

	path = NULL;
	cmd = cmd_s; 
	//for
	while (cmd)
	{
		in_out_s[0] = dup(0);
		in_out_s[1] = dup(1);
		ft_strdel(&path);
		path = msh_get_path(cmd->args[0], g_info.env);
		if(!path)
			break ;
		if (cmd->redirects)
		{
			msh_custom_redirect(fd_cur, cmd);
			if (cmd->input)
			{
				
				dup2(fd_cur[0], 0);
				close(fd_cur[0]);
				
			}
			if (cmd->out)
			{
					dup2(fd_cur[1], 1);
				close(fd_cur[1]);
			}
				
			msh_simple_execute(cmd, path, g_info.env);
			if (cmd->input)
			{
				dup2(in_out_s[0], 0);
				close(in_out_s[0]);
			}
			if (cmd->out)
			{
				dup2(in_out_s[1], 1);
				close(in_out_s[1]);
			}
			break;
		}
		else if (cmd->prev && cmd->prev->piped)
		{
			in_out_s[0] = dup(0);
			dup2(fd_cur[0], 0);
			close(fd_cur[0]);
		}
		if (cmd->piped)
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("Pipe");
				break ;
			}
			in_out_s[1] = dup(1);
			dup2(fd_cur[1], 1);
			close(fd_cur[1]);
		}



		// in_out_s[0] = dup(0);
		// in_out_s[1] = dup(1);
		// if (cmd->redirects)
		// 	msh_custom_redirect(fd_cur, cmd);//open(cmd->input, O_RDONLY);
		// else
		// 	fd_cur[0] = dup(in_out_s[0]);
		// //for
		// dup2(fd_cur[0], STDIN_FILENO);
		// close(fd_cur[0]);
		// if (cmd->next == NULL) // if last command
		// {
		// 	if (!cmd->out)
		// 		fd_cur[1] = dup(in_out_s[1]);
		// }
		// else if (cmd->piped)
		// {
		// 	pipe(fd_pipe);
		// 	fd_cur[1] = fd_pipe[1];
		// 	fd_cur[0] = fd_pipe[0];
		// }
		// dup2(fd_cur[1], STDOUT_FILENO);
		// close(fd_cur[1]);


		// in_out_s[0] = dup(0);
		// in_out_s[1] = dup(1);
		// if (cmd->redirects)
		// 	msh_custom_redirect(fd_cur, cmd);
		// if (!cmd->input)
		// 	fd_cur[0] = dup(in_out_s[0]);
		// //for
		// dup2(fd_cur[0], STDIN_FILENO);
		// close(fd_cur[0]);
		// if (cmd->next == NULL && !cmd->out)// if last command
		// 	fd_cur[1] = dup(in_out_s[1]);
		// else if (cmd->piped)
		// {
		// 	pipe(fd_pipe);
		// 	fd_cur[1] = fd_pipe[1];
		// 	fd_cur[0] = fd_pipe[0];
		// }
		// dup2(fd_cur[1], STDOUT_FILENO); //set out
		// close(fd_cur[1]);
		ret = fork();
		if (ret == 0)
		{
			if (!msh_buildins(cmd, 1))
			{
				s = cmd->args[0];
				cmd->args[0] = path;
				ft_strdel(&s);
				if (execve(cmd->args[0], cmd->args, env) == -1)//(cmd->args[0], cmd->args, env) == -1)
				{
					perror(cmd->args[0]);
					exit(1);
				}
				
			}
		}
		int	status;
		if (!cmd->background ) //wait for last command
			waitpid(ret, &status, 0);
		if (cmd->redirects)
		{
			if (cmd->input)
			{
				dup2(in_out_s[0], 0);
				close(in_out_s[0]);
			}
			if (cmd->out)
			{
				dup2(in_out_s[1], 1);
				close(in_out_s[1]);
			}
		}
		else if (cmd->prev && cmd->prev->piped)
		{
		   dup2(in_out_s[0], 0);
		   close(in_out_s[0]);
		}
		if (cmd->piped)
		{         
		   dup2(in_out_s[1], 1);
		   close(in_out_s[1]);
		}
		cmd = cmd->next;
	}
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
