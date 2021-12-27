// void	msh_help_parse_r_redirect(char *str, int *index)
// {
// 	(void)str;
// 	(void)index;
// 	int	is_cmd;
// 	int i;
// //	char *tmp;

// 	i = *index;
// 	if (ft_strcmp(g_info.cur_cmd->args[0] , "<") == 0 && g_info.cur_cmd->num_args == 3)
// 		ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[2]);
// 	else if (ft_strcmp(g_info.cur_cmd->args[0] , "<"))
// 		is_cmd = 0;
// 	else
// 		is_cmd = 1;
// 	while (i < g_info.cur_cmd->num_args)
// 	{
// 		if (msh_check_syntax(g_info.cur_cmd->args[i], i, '<', ft_strlen(g_info.cur_cmd->args[i])))
// 		{
// 			msh_add_redirect(&g_info.cur_cmd->input, ft_strdup(g_info.cur_cmd->args[i] + 1));
// 			ft_strdel(&g_info.cur_cmd->args[i]);	
// 		}
// 		else if (!ft_strcmp(g_info.cur_cmd->args[i], "<")
// 			&& i + 1 < g_info.cur_cmd->num_args)
// 		{
// 			if (is_cmd && i + 2 < g_info.cur_cmd->num_args && ft_strcmp(g_info.cur_cmd->args[i + 3] , "<") && is_cmd--)
// 				ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[i + 3]);
// 			ft_strdel(&g_info.cur_cmd->args[i]);
// 			msh_add_redirect(&g_info.cur_cmd->input, g_info.cur_cmd->args[i + 1]);
// 			g_info.cur_cmd->args[i + 1] = NULL;
// 			i++;
// 		}
// 		i++;
// 	}
// 	msh_concat_args(g_info.cur_cmd);
// 	*index = 0;
// 	// while (str[*index] != '\0' && str[*index] != ';' && str[*index] != '|')
// 	// {
// 	// 	while (str[*index] && str[*index] == ' ')
// 	// 		(*index)++;
// 	// 	start = *index;
// 	// 	while (str[*index] && str[*index] != ' ' && str[*index] != '<')
// 	// 		(*index)++;
// 	// 	if (is_need_cmd && str[*index] == ' ')
// 	// 	msh_add_redirect(&g_info.current_command->input, ft_strndup(str + start, *index - start));
// 	// 	if (str[*index] == '<')
// 	// 		(*index)++;
// 	// }

// 	// int	start;
// 	// int mem_start_index;

// 	// start = *length;
// 	// mem_start_index = start_index;
// 	// while (str[start_index] == '>')
// 	//  	start_index++;
// 	// if (start_index - mem_start_index > 1)
// 	// {
// 	// 	g_info.current_command->specials = ERROR;
// 		// msh_error(str, "Mishelle: syntax error near unexpected token",
// 		// 	str + mem_start_index , start_index - mem_start_index);
// 	// }
// 	// start = *length;
// 	// if (g_info.current_command->number_args > 1)
// 	// 	g_info.current_command->out_file = g_info.current_command->args[1];
// 	// else
// 	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
// 	// 		str + mem_start_index , start_index - mem_start_index);
// 	// int	length;
// 	// int mem_start_index;
	
// 	// if (g_info.current_command->number_args > 1)
// 	// 	g_info.current_command->out_file = g_info.current_command->args[1];
// 	// else
// 	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
// 	// 		str + mem_start_index , start_index - mem_start_index);
// }


// char	*msh_read_fd(int fd)
// {
// 	int		ret;
// 	char	*tmp;
// 	char	buff[1024];
// 	char	*result;

// 	result = NULL;
// 	ft_bzero(buff, 1024);
// 	if (fd < 0)
// 		return (NULL);
// 	while ((ret = read(fd, buff, 1024)) > 0)
// 	{
// 		if (!result)
// 			result = ft_strdup(buff);
// 		else
// 		{
// 			tmp = ft_strjoin(result, buff);
// 			ft_strdel(&result);
// 			result = tmp;
// 		}
// 	}
// 	return (result);
// }


// char *msh_get_path(char *cmd_name, char **env)
// {
// 	int		pid;
// 	int		fd[2];
// 	char	*path;
// 	char	*cmd[3];
// 	char	fds[2];

// 	fds[0] = dup(STDIN_FILENO);
// 	fds[1] = dup(STDOUT_FILENO);
// 	cmd[0] = "/usr/bin/which";
// 	cmd[1] = cmd_name;
// 	cmd[2] = NULL;
// 	path = NULL;
// 	if (pipe(fd) < 0)
// 		perror("Error");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
		
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (execve("/usr/bin/which", cmd, env) == -1)
// 		{
// 			perror("Pathfinder:");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[1]);
// 	close(fd[0]);
	
// 	waitpid(0, NULL, 0);
// 	path = msh_read_fd(0);
// 	if (path)
// 		path[ft_strlen(path) - 1] = '\0';
// 	dup2( fds[1], STDOUT_FILENO);
// 	dup2(fds[0], STDIN_FILENO);
	
	
// 	close(fds[0]);
// 	close(fds[1]);
// 	return (path);
// }



// char *msh_multy_pipe(t_command *cmds, char **env)
// {
// 	int		pid;
// 	int		fd[2];
// 	char	*result;
// 	int		file;

// 	result = NULL;
// 	if (pipe(fd) < 0)
// 		perror("Error");
// 	if (cmds->input_file)
// 	{
// 		file = open(cmds->input_file, O_RDONLY, 0777);
// 		dup2(fd[0], STDIN_FILENO);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (execve(cmds->args[0], cmds->args, env) == -1)
// 		{
// 			perror("Execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	waitpid(0, NULL, 0);
// 	if (cmds->out_file)
// 	{
// 		file = open(cmds->out_file, O_CREAT | O_WRONLY, 0777);
// 		dup2(fd[0], file);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		result = msh_read_fd(0);
// 	}
// 	close(fd[1]);
// 	close(fd[0]);
// 	return (result);
// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *re = msh_get_path(NULL, env);
// 	if (re == NULL)
// 		printf("NULL\n");
// 	printf("%s", re);
// 	ft_strdel(&re);
// 	return (0);
// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_command	*cmd;

// 	cmd = malloc(sizeof(t_command));
// 	cmd->args = argv + 1;
// 	char *re = msh_multy_pipe(cmd, env);
// 	if (re == NULL)
// 		printf("NULL\n");
// 	printf("%s", re);
// 	ft_strdel(re);
// 	return (0);
// }
