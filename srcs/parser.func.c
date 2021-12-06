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
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + index , ft_strlen(str) - index);
	}
}

void	msh_redirect_parse(char *str, int *length)
{
	(void)str;
	(void)length;
	t_command	*cmd;
	int 		i;

	i = 0;
	cmd = g_info.cur_cmd;
	while (cmd->args[i])
	{
		if (ft_strnstr(cmd->args[i], ">>", 3))
			msh_help_parse_d_redirect(cmd->args[i], &i);
		else if (ft_strnstr(cmd->args[i], "<<", 3))
			msh_help_parse_rd_redirect(cmd->args[i], &i);
		else if (ft_strchr(cmd->args[i], '<'))
			msh_help_parse_r_redirect(cmd->args[i], &i);
		else if (ft_strchr(cmd->args[i], '>'))
			msh_help_parse_redirect(cmd->args[i], &i);
		i++;
	}
}

void	msh_help_parse_semi(char *str, int *length)
{
	msh_redirect_parse(str, length);
}

void	msh_help_parse_pipe(char *str, int *index)
{
	(void)str;
	(void)str;
	(*index)++;
	g_info.cur_cmd->piped = 1;
	msh_redirect_parse(str, index);
}

void	msh_concat_args(t_command *cmd)
{
	int		i;
	int		j;
	int		num;
	int		k;
	char	**tmp;
	char *hh;

	i = -1;
	num = 0;
	k = 0;
	while (cmd->args[++i])
		num++;
	j = cmd->num_args;
	while (j >= 0 && cmd->args[--j])
		num++;
	if (num)
	{
		tmp = cmd->args;
		cmd->args = malloc(sizeof(char) * (num + 1));
		while (k < i)
		{
			hh = tmp[k];
			cmd->args[k] = hh;//tmp[k];
			k++;
		}
		while (++j < cmd->num_args)
		{
			hh = tmp[j];
			cmd->args[k] = hh;// tmp[k];
			k++;
		}
		//ft_delptr((void **)tmp);
		cmd->num_args = num;
	}

	for( int i = 0; cmd->args[i]; i++)
	{
		printf("%s | ", cmd->args[i]);
	}
	printf("end of command\n");
}

void	msh_help_parse_redirect(char *str, int *index)
{
	(void)str;
	int 		is_cmd;
	int			i;

	i = *index;
	is_cmd = 0;
	msh_check_syntax(str, '>', 1);
	if (ft_strcmp(g_info.cur_cmd->args[0] , ">") == 0
			&& g_info.cur_cmd->num_args == 3 
			&& i + 2 < g_info.cur_cmd->num_args)
		ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[i + 2]);
	else if (ft_strcmp(g_info.cur_cmd->args[0] , ">"))
		is_cmd = 0;
	else
		is_cmd = 1;
	while (i < g_info.cur_cmd->num_args)
	{
		msh_check_syntax(g_info.cur_cmd->args[i], '>', 1);
		if (!ft_strcmp(g_info.cur_cmd->args[i], ">")
			&& i + 1 < g_info.cur_cmd->num_args)
		{
			if (is_cmd && i + 2 < g_info.cur_cmd->num_args && ft_strcmp(g_info.cur_cmd->args[i + 3] , ">") && is_cmd--)
				ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[i + 3]);
			ft_strdel(&g_info.cur_cmd->args[i]);
			msh_add_redirect(&g_info.cur_cmd->input, g_info.cur_cmd->args[i + 1]);
			g_info.cur_cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	msh_concat_args(g_info.cur_cmd);
	*index = 0;
}

void	msh_help_parse_r_redirect(char *str, int *index)
{
	(void)str;
	(void)index;
	int	is_cmd;
	int i;
//	char *tmp;

	i = *index;
	is_cmd = 0;
 	msh_check_syntax(str, '<', 1);
	if (ft_strcmp(g_info.cur_cmd->args[0] , "<") == 0 && g_info.cur_cmd->num_args == 3)
		ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[2]);
	else if (ft_strcmp(g_info.cur_cmd->args[0] , "<"))
		is_cmd = 0;
	else
		is_cmd = 1;
	while (i < g_info.cur_cmd->num_args)
	{
		msh_check_syntax(str, '<', 1);
		if (!ft_strcmp(g_info.cur_cmd->args[i], "<")
			&& i + 1 < g_info.cur_cmd->num_args)
		{
			if (is_cmd && i + 2 < g_info.cur_cmd->num_args && ft_strcmp(g_info.cur_cmd->args[i + 3] , ">") && is_cmd--)
				ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[i + 3]);
			ft_strdel(&g_info.cur_cmd->args[i]);
			msh_add_redirect(&g_info.cur_cmd->input, g_info.cur_cmd->args[i + 1]);
			g_info.cur_cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	msh_concat_args(g_info.cur_cmd);
	*index = 0;
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

void	msh_help_parse_d_redirect(char *str, int *length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_rd_redirect(char *str, int *length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_ampersand(char *str, int *length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_r_redirect_amp(char *str, int *length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_rd_redirect_amp(char *str, int *length)
{
	(void)str;
	(void)length;
}
