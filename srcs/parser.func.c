#include "../includes/main.h"
//
void	msh_check_syntax(char *str, int c, int len_cmp)
{
	int index;
	

	index = 0;
	if (!ft_strchr(str, c))
		return ;
	while (str[index] == c)
	 	index++;
	if (index > len_cmp)
	{
		g_info.current_command->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + index , ft_strlen(str) - index);
	}
}


void	msh_redirect_parse(char *str, int length)
{
	(void)str;
	(void)length;
	t_command	*cmd;
	int 		i;

	i = 0;
	cmd = g_info.current_command;
	while (i < cmd->number_args)
	{
		if (ft_strnstr(cmd->args[i], ">>", 3))
			msh_help_parse_d_redirect(cmd->args[i], i);
		else if (ft_strnstr(cmd->args[i], "<<", 3))
			msh_help_parse_rd_redirect(cmd->args[i], i);
		else if (ft_strchr(cmd->args[i], '<'))
			msh_help_parse_r_redirect(cmd->args[i], i);
		else if (ft_strchr(cmd->args[i], '>'))
			msh_help_parse_redirect(cmd->args[i], i);
		i++;
	}
}

void	msh_help_parse_semi(char *str, int length)
{
	msh_redirect_parse(str, length);
}

void	msh_help_parse_pipe(char *str, int index)
{
	(void)str;
	(void)str;
	g_info.current_command->piped = 1;
	msh_redirect_parse(str, index);
}

void	msh_help_parse_redirect(char *str, int index)
{
	(void)str;
	int is_need_cmd;
	char	*tmp;
	int i;

	i = index;
	is_need_cmd = 0;
	msh_check_syntax(str, '>', 1);
	if (ft_strcmp(g_info.current_command->args[0] , ">") == 0 && g_info.current_command->number_args == 3)
		ft_swap_strs(g_info.current_command->args[0], g_info.current_command->args[2]);
	else if (g_info.current_command->number_args == 1 && ft_strcmp(g_info.current_command->args[0] , ">"))
		is_need_cmd = 0;
	else
		is_need_cmd = 1;
	while (i < g_info.current_command->number_args)
	{
		msh_check_syntax(g_info.current_command->args[i], '>', 1);
		if (!ft_strcmp(g_info.current_command->args[i], ">")
			&& i + 1 < g_info.current_command->number_args)
		{
			tmp = g_info.current_command->args[i];
			msh_add_redirect(&g_info.current_command->input, NULL);
			ft_swap_strs(g_info.current_command->input->prev->file, tmp);
			i++;
		}
		i++;
	}
	
	// int	start;
	// int mem_start_index;

	// start = *length;
	// mem_start_index = start_index;
	// while (str[start_index] == '>')
	//  	start_index++;
	// if (start_index - mem_start_index > 1)
	// {
	// 	g_info.current_command->specials = ERROR;
	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
	// 		str + mem_start_index , start_index - mem_start_index);
	// }
	// start = *length;
	// if (g_info.current_command->number_args > 1)
	// 	g_info.current_command->out_file = g_info.current_command->args[1];
	// else
	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
	//		str + mem_start_index , start_index - mem_start_index);
}

void	msh_help_parse_r_redirect(char *str, int index)
{
	(void)str;
	(void)index;
	int	is_need_cmd;
	int i;
	char *tmp;

	i = index;
	is_need_cmd = 0;
 	msh_check_syntax(str, '<', 1);
	if (ft_strcmp(g_info.current_command->args[0] , "<") == 0 && g_info.current_command->number_args == 3)
		ft_swap_strs(g_info.current_command->args[0], g_info.current_command->args[2]);
	else if (ft_strcmp(g_info.current_command->args[0] , "<"))
		is_need_cmd = 0;
	else
		is_need_cmd = 1;
	while (i < g_info.current_command->number_args)
	{
		msh_check_syntax(str, '<', 1);
		if (!ft_strcmp(g_info.current_command->args[i], "<")
			&& i + 1 < g_info.current_command->number_args)
		{
			tmp = g_info.current_command->args[i + 1];
			msh_add_redirect(&g_info.current_command->input, NULL);
			ft_swap_strs(g_info.current_command->input->prev->file, tmp);
			//ft_swap_strs(g_info.current_command->input->prev->file, g_info.current_command->args[i]);
			i++;
		}
		i++;
	}
	// while (str[*index] != '\0' && str[*index] != ';' && str[*index] != '|')
	// {
	// 	while (str[*index] && str[*index] == ' ')
	// 		(*index)++;
	// 	start = *index;
	// 	while (str[*index] && str[*index] != ' ' && str[*index] != '<')
	// 		(*index)++;
	// 	if (is_need_cmd && str[*index] == ' ')
	// 	msh_add_redirect(&g_info.current_command->input, ft_strndup(str + start, *index - start));
	// 	if (str[*index] == '<')
	// 		(*index)++;
	// }

	// int	start;
	// int mem_start_index;

	// start = *length;
	// mem_start_index = start_index;
	// while (str[start_index] == '>')
	//  	start_index++;
	// if (start_index - mem_start_index > 1)
	// {
	// 	g_info.current_command->specials = ERROR;
		// msh_error(str, "Mishelle: syntax error near unexpected token",
		// 	str + mem_start_index , start_index - mem_start_index);
	// }
	// start = *length;
	// if (g_info.current_command->number_args > 1)
	// 	g_info.current_command->out_file = g_info.current_command->args[1];
	// else
	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
	// 		str + mem_start_index , start_index - mem_start_index);
	// int	length;
	// int mem_start_index;
	
	// if (g_info.current_command->number_args > 1)
	// 	g_info.current_command->out_file = g_info.current_command->args[1];
	// else
	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
	// 		str + mem_start_index , start_index - mem_start_index);
}

void	msh_help_parse_d_redirect(char *str, int length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_rd_redirect(char *str, int length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_ampersand(char *str, int length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_r_redirect_amp(char *str, int length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_rd_redirect_amp(char *str, int length)
{
	(void)str;
	(void)length;
}
