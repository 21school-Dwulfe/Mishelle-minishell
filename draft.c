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
