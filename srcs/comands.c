#include "../includes/main.h"

void	msh_print_dir_(void)
{
	char str[512];

	getcwd(str, sizeof(str));
	printf("%s ", str);
}

void	msh_insert_argument(t_s_command *cmd, char *argument)
{
	cmd->arguments[cmd->num_of_args] = argument;
	cmd->num_of_args++;
}

void	msh_insert_simple_command(t_command *cmd, t_s_command *simple_cmd)
{
	cmd->simple_commands[cmd->num_of_simple_commands] = simple_cmd;
	cmd->num_of_simple_commands++;
}