#include "../includes/main.h"

void	msh_help_parse_semi(char *str, int *length)
{
	(void)str;
	(void)length;
}

void	msh_help_parse_pipe(char *str, int *length)
{
	(void)str;
	(*length)++;
	g_info.current_command->piped = 1;
}

void	msh_help_parse_redirect(char *str, int *length)
{
	int	start;

	start = *length;
	while (str[*length] == '>')
		(*length)++;
	if (*length - start == 2)
		g_info.current_command->specials = D_REDIRECT; 
	else if (*length - start > 2)
		g_info.current_command->specials = ERROR;
	start = *length;
	while (str[*length] && str[*length] != ' ' && str[*length] != '>')
		(*length)++;
	g_info.current_command->out_file = ft_strndup(str + start, *length - start);
}

void	msh_help_parse_r_redirect(char *str, int *length)
{
	int	start;

	start = *length;
	while (str[*length] == '<')
		(*length)++;
	if (*length - start == 2)
		g_info.current_command->specials = RD_REDIRECT; 
	else if (*length - start > 2)
		g_info.current_command->specials = ERROR;
	start = *length;
	while (str[*length] && str[*length] != ' ' && str[*length] != '<')
		(*length)++;
	g_info.current_command->input_file = ft_strndup(str + start, *length - start);
}

// void	msh_help_parse_ampersand(char *str, int *length)
// {

// }

// void	msh_help_parse_d_redirect(char *str, int *length)
// {

// }

// void	msh_help_parse_rd_redirect(char *str, int *length)
// {

// }

// void	msh_help_parse_r_redirect_amp(char *str, int *length)
// {

// }

// void	msh_help_parse_rd_redirect_amp(char *str, int *length)
// {

// }
