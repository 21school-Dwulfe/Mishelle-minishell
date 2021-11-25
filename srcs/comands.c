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
	int 	i;

	i = 0;
	while (i < cmd->number_args)
		ft_putstr_fd(cmd->arguments[i++], 1);
	if (cmd->number_args > 1 && (!ft_strnstr(cmd->arguments[1], "-n ", 3)))
		write(1, "\n", 1);
}

void	msh_custom_env(t_command *cmd)
{
	(void)cmd;

}

void	msh_custom_cd(t_command *cmd)
{
	chdir(cmd->arguments[0]);
}

void msh_modify_env_var(char *new_value)
{
	
}

int	msh_check_if_exist()
{
	
}

// -n -p -f
void	msh_custom_export(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->number_args > 1)
	{
		while (i < cmd->number_args)
		{
			if (msh_check_if_exist(cmd->arguments))
				msh_modify_env_var(cmd->arguments[i]);
			else
				msh_create_env_var(cmd->arguments[i]);
			i++;
		}

	}
	else
	{
		while (g_info.env[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(g_info.env[i], 1);
			i++;
		}
	}
}

void	msh_custom_unset(t_command *cmd)
{
	(void)cmd;
}

