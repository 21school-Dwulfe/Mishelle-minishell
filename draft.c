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



// int	check_is_opened(char c)
// {
// 	static int i;
// 	static int ch;

// 	if (c == 0)
// 		return (0);
// 	if (i == 0 && (c == '\'' || c == '\"'))
// 	{
// 		i = 1;
// 		ch = c;
// 	}
// 	else if (i > 0 && c != ch)
// 		return (ch);
// 	else if (i > 0 )
// 	{
// 		i = 0;
// 		ch = 0;
// 	}
// 	return (ch);
// }

// int	count_str(char	*str, int c)
// {
// 	int	i;
// 	int flag;
// 	int count;

// 	i = -1;
// 	flag = 0;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (flag == 0 && check_is_opened(str[i]) && ++i)
// 		{
// 			while (check_is_opened(str[i]))
// 				i++;
// 			count++;
// 			flag = 0;
// 		}
// 		else if (str[i] == c)
// 			flag = 0;
// 		else if (flag == 0)
// 		{
// 			count++;
// 			flag = 1;
// 		}
// 	}
// 	return (count);
// }

// char	*msh_get_quotes_str(char *str, int *i)
// {
// 	int start;
// 	char *result;

// 	start = *i;
// 	while (check_is_opened(str[*i]))
// 		*i = *i + 1;
// 	*i = *i + 1;
// 	result = ft_strndup(str + start, *i - 1 - start);
// 	return (result);
// }

// char	*ft_str_smart_join(char *s1, char *s2)
// {
// 	if (s1 == NULL && s2)
// 		return (s2);
// 	else if (s1 && s2 == NULL)
// 		return (s1);
// 	return (ft_strjoin(s1, s2));
// }

// char	**msh_split(char *str, int c)
// {
// 	int		i;
// 	int		j;
// 	int		start;
// 	char	**result;
// 	int		counter;
// 	char	*tmp[2];

// 	i = 0;
// 	j = 0;
// 	ft_bzero(tmp, sizeof(char) * 2);
// 	counter = count_str(str, c);
// 	result = (char **)malloc((counter + 1) * sizeof(char *));
// 	ft_bzero(result, (counter + 1) * sizeof(char *));
// 	while (str[i])
// 	{	
// 		while (str[i] && str[i] == c)
// 				i++;
// 		while (str[i] && str[i] != c)
// 		{
// 			if (check_is_opened(str[i]) && ++i)
// 			{
// 				tmp[0] = msh_get_quotes_str(str, &i);
// 				if (tmp[0] != NULL && result[j])
// 				{
// 					tmp[1] = result[j];
// 					result[j] = ft_strjoin(tmp[1], tmp[0]);
// 					ft_strdel(&tmp[1]);
// 					ft_strdel(&tmp[0]);
// 				}
// 				else
// 					result[j] = tmp[0];
// 			}
// 			if ((result[j] && str[i] == c) || str[i] == '\0')// if next char after quotes == space
// 				break ;
// 			if (str[i] && str[i] != '\'' && str[i] != '\"')
// 			{
// 				start = i;
// 				while(str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != c)
// 					i++;
// 				if (result[j] != 0 && start != i)
// 				{
// 					tmp[1] = result[j];
// 					tmp[0] = ft_strndup(str + start, i - start);
// 					result[j] = ft_str_smart_join(tmp[1], tmp[0]);
// 					ft_strdel(&tmp[1]);
// 					ft_strdel(&tmp[0]);
// 				}
// 				else if (start != i)
// 					result[j] = ft_strndup(str + start, i - start);
// 			}
			
// 		}
// 		if (j > 0 && result[j - 1] == NULL)
// 				ft_arrstr_del(result, j);
// 		else if (j < counter)
// 			j++;
// 	}
// 	result[j] = (void *)0;
// 	return (result);
// }




// int	msh_dollar_common_case(t_command *cmd, char *tmp, char **env, int *k)
// {
// 	int		i[3];
// 	char	*temp[6];

// 	ft_bzero(temp, sizeof(char) * 6);
// 	ft_bzero(i, sizeof(int) * 3);
// 	temp[1] = tmp;
// 	temp[2] = msh_get_env_by_key(env, temp[1] + 1);
// 	if (temp[2])
// 	{
// 		if (i[1] != 0)
// 		{
// 			if (k[2] == 1)
// 			{
// 				temp[3] = ft_strndup_se(temp[0], 0, '$');
// 				temp[4] = ft_strjoin(temp[3], temp[2]);
// 			}
// 			if (k[1] == 1)
// 				cmd->args[k[0]] = temp[4];
// 			else
// 			{
// 				temp[5] = ft_strjoin(cmd->args[k[0]], temp[4]);
// 				ft_strdel(&cmd->args[k[0]]);
// 				cmd->args[k[0]] = temp[5];
// 			}
// 			i[2] = ft_strlen(temp[1]);
// 			ft_strdel(&temp[3]);
// 		}
// 		else
// 			cmd->args[k[0]] = ft_strdup(temp[2]);
// 	}
// 	else
// 	{
// 		ft_memset(temp[1], '\0', ft_strlen(temp[1]));
// 		temp[1] = temp[0];
// 		cmd->args[k[0]] = msh_concat_str(temp[1], ft_strlen(temp[0]), NULL);
// 	}
// 	return (ft_strlen(temp[1]));
// }

// void	msh_evaluate_env_call_if_exist(t_command *cmd, char **env)
// {
// 	int		i[5];
// 	int		k[3];
// 	char	*temp[6];
// 	int 	j;
// 	int 	count_dollars;

// 	j = 0;
// 	ft_bzero(i, sizeof(int) * 5);
// 	ft_bzero(temp, sizeof(char *) * 6);
// 	while (i[0] < cmd->num_args)
// 	{
// 		j = 0;
// 		temp[0] = cmd->args[i[0]];
// 		count_dollars = ft_ch_count(temp[0], '$');
// 		while (j < count_dollars)
// 		{
// 			temp[1] = ft_strchr(temp[0], '$');
// 			i[1] = ft_index_of(temp[0], '$');
// 			if (temp[1] && temp[1][1] != '?' &&  temp[0][0] != '\'')// need to set flag
// 			{
// 				k[0] = i[0];
// 				k[1] = count_dollars;
// 				k[2] = j;
// 				i[4] = msh_dollar_common_case(cmd, temp[1], env, k);
				
// 			}
// 			else if (temp[1] && temp[1][1] == '?' && temp[0][0] != '\'')
// 			{
// 				i[4] = msh_dollar_error_case(cmd, temp[1], i[0]);
// 			}
// 			temp[0] = temp[0] + i[4];
// 			j++;
// 		}
// 		i[0]++;
// 	}
// }

// int	msh_dollar_error_case(t_command *cmd, char *tmp, int j)
// {
// 	int		i[3];
// 	char	*temp[6];

// 	ft_bzero(i, sizeof(int) * 3);
// 	ft_bzero(temp, sizeof(char *) * 6);
// 	temp[0] = cmd->args[j];
// 	temp[2] = tmp;
// 	temp[3] = ft_itoa(msh_read_error_code());
// 	temp[4] = ft_strjoin(temp[3], temp[1] + 2);
// 	if (temp[0][0] != '$')
// 	{
// 		temp[5] = ft_strndup_se(temp[0], 0, '$');
// 		temp[1] = ft_strjoin(temp[5], temp[4]);
// 		i[2] = 6;
// 	}
// 	else
// 	{
// 		temp[1] = ft_strdup(temp[4]);
// 		i[2] = 5;
// 	}
// 	cmd->args[j] = temp[1];
// 	while (1 != --i[2])
// 		ft_strdel(&temp[i[2]]);
// 	ft_strdel(&temp[0]);
// 	return (2);
// }

// char	*msh_dollar_error_case(char **args, char *tmp, int j)
// {
// 	int		i[3];
// 	char	*temp[6];

// 	ft_bzero(i, sizeof(int) * 3);
// 	ft_bzero(temp, sizeof(char *) * 6);
// 	temp[0] = args[j];
// 	temp[2] = tmp;
// 	temp[3] = ft_itoa(msh_read_error_code());
// 	temp[4] = ft_strjoin(temp[3], temp[1] + 2);
// 	if (temp[0][0] != '$')
// 	{
// 		temp[5] = ft_strndup_se(temp[0], 0, '$');
// 		temp[1] = ft_strjoin(temp[5], temp[4]);
// 		i[2] = 6;
// 	}
// 	else
// 	{
// 		temp[1] = ft_strdup(temp[4]);
// 		i[2] = 5;
// 	}
// 	args[j] = temp[1];
// 	while (1 != --i[2])
// 		ft_strdel(&temp[i[2]]);
// 	ft_strdel(&temp[0]);
// 	return (temp[1]);
// }
