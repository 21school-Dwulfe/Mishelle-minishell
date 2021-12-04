#include "../includes/main.h"

void	msh_help_parse_semi(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}
void	msh_help_parse_pipe(char *str, int *length, int start_index)
{
	int i;
	(void)str;
	(void)start_index;
	(*length)++;
	g_info.current_command->piped = 1;
	char	**tmp;

	(void)str;
	i = 0;
	while (i < g_info.current_command->number_args)
	{
		if (!ft_strcmp(g_info.current_command->args[i], "<")
			&& i + 1 <= g_info.current_command->number_args)
		{
			msh_add_command(&g_info.current_command, );
		}
		i++;
	}
	//msh_help_parse_redirect();
}

int	msh_is_not_specials(int c)
{
	if (c != '<' && c != '>' && c != '|' && c != ';')
		return (1);
	return (0);
}

void	msh_help_parse_redirect(char *str, int *length, int start_index)
{
	int	start;
	int mem_start_index;

	start = *length;
	mem_start_index = start_index;
	while (str[start_index] == '>')
	 	start_index++;
	if (start_index - mem_start_index > 1)
	{
		g_info.current_command->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + mem_start_index , start_index - mem_start_index);
	}
	start = *length;
	if (g_info.current_command->number_args > 1)
		g_info.current_command->out_file = g_info.current_command->args[1];
	else
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + mem_start_index , start_index - mem_start_index);
}

void	msh_help_parse_r_redirect(char *str, int *index, int begin_of_str)
{
	int	start;
	int mem_start_index;

	start = *length;
	mem_start_index = start_index;
	while (str[start_index] == '>')
	 	start_index++;
	if (start_index - mem_start_index > 1)
	{
		g_info.current_command->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + mem_start_index , start_index - mem_start_index);
	}
	start = *length;
	if (g_info.current_command->number_args > 1)
		g_info.current_command->out_file = g_info.current_command->args[1];
	else
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + mem_start_index , start_index - mem_start_index);
	int	length;
	int mem_start_index;
	
	if (g_info.current_command->number_args > 1)
		g_info.current_command->out_file = g_info.current_command->args[1];
	else
		msh_error(str, "Mishelle: syntax error near unexpected token",
			str + mem_start_index , start_index - mem_start_index);
}

void	msh_help_parse_ampersand(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}

void	msh_help_parse_d_redirect(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}

void	msh_help_parse_rd_redirect(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}

void	msh_error(char *str, char *message, char *token_str, int token_len)
{
	int i;

	i = 0;
	(void)str;
	while (message[i])
		i++;
	write(2, message, i);
	write(2, " `", 2);
	write(2, token_str, token_len);
	write(2, "'", 1);
//	ft_strdel(str);
	msh_struct_clear();
	exit(1);
}

void	msh_help_parse_r_redirect_amp(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}

void	msh_help_parse_rd_redirect_amp(char *str, int *length, int start_index)
{
	(void)str;
	(void)length;
	(void)start_index;
}
