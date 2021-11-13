#include "../includes/main.h"

void	msh_custom_pwd(t_command *cmd)
{
	char str[512];

	(void)cmd;
	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
void	msh_custom_exit(t_command *cmd)
{
	(void)cmd;
	exit(1);
}

void	msh_custom_echo(t_command *cmd)
{
	(void)cmd;
	int i;

	i = 0;
	while (i < cmd->number_args)
	{
		if (cmd->arguments[i])
		{

		}
	}
	cmd->arguments;
	ft_putstr_fd();
	//temporary execution
	
}

void	msh_custom_env(t_command *cmd)
{
	(void)cmd;

}

void	msh_custom_cd(t_command *cmd)
{
	chdir(cmd->arguments[0]);
}

void	msh_custom_export(t_command *cmd)
{
	(void)cmd;

}

void	msh_custom_unset(t_command *cmd)
{
	(void)cmd;
}

