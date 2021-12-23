#include "../includes/main.h"

int	msh_custom_pwd(t_command *cmd)
{
	char *str;

	str = NULL;
	(void)cmd;
	str = getcwd(str, sizeof(str) * 512);
	ft_putendl_fd(str, 1);
	ft_strdel(&str);
	return (1);
}

int	msh_custom_exit(t_command *cmd)
{
	(void)cmd;
	exit(0);
	return (1);
}

int	msh_custom_echo(t_command *cmd)
{
	short	is_nl;
	int		len;
	int		l[4];
	char	*tmp[4];

	is_nl = 1;
	len = 1;
	ft_bzero(l, sizeof(int) * 4);
	ft_bzero(tmp, sizeof(char *) * 4);
	tmp[0] = ft_strchr(cmd->args[1], '-');
	if (tmp[0] && *(tmp[0] + 1) == 'n' && (--is_nl == 0))
			len = 2;
	if (cmd->num_args > 1 && !(len == 2 && cmd->num_args == 2))
	{
		l[2] = len;
		while (l[2] < cmd->num_args)
			l[0] += ft_strlen(cmd->args[l[2]++]);
		tmp[1] = ft_calloc(sizeof(char), (l[0] + cmd->num_args - 2));
		while (len < cmd->num_args)
		{
			l[1] = (int)ft_strlcat(tmp[1], cmd->args[len], (l[0] + cmd->num_args - 1));
			if (len != cmd->num_args - 1)
				tmp[1][l[1]] = ' ';
			len++;
		}
		ft_putstr_fd(tmp[1], 1);
		ft_strdel(&tmp[1]);
	}
	if (is_nl)
		ft_putstr_fd("\n", 1);
	return (1);
}

int	msh_custom_env(t_command *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	while (g_info.env[i])
	{
		if (ft_index_of(g_info.env[i], '=') != -1)
			ft_putendl_fd(g_info.env[i], 1);
		i++;
	}
	return (1);
}

void	msh_export_add(t_command	*cmd)
{
	int		i;
	int		arg_in_env;

	i = 1;
	while (i < cmd->num_args)
	{
		if (msh_export_invalid(cmd->args[i]))
		{
			msh_export_error(cmd->args[i]);
			break ;
		}
		arg_in_env = msh_env_str(g_info.env, cmd->args[i]);
		if (arg_in_env)
			msh_modify_env_var(&g_info.env[arg_in_env], cmd->args[i]);
		else
			g_info.env = msh_create_env_var(cmd->args[i]);
		i++;
	}
}

// -n -p -f
int	msh_custom_export(t_command *cmd)
{
	int		i;
	int		index;

	i = 1;
	for (int i= 0; i < ft_str_count(g_info.env); i++)
	{
		printf("%d %s\n", i + 1, g_info.env[i]);
	}
	if (cmd->num_args > 1)
		msh_export_add(cmd);
	else
		while (g_info.env[i])
		{
			ft_putstr_fd("declare -x ", 1);
			index = ft_index_of(g_info.env[i], '=');
			if (index > -1)
			{
				write(1, g_info.env[i], index + 1);
				write(1,"\"", 1);
				if (ft_strlen((g_info.env[i]) + index + 1) > 0)
					ft_putstr_fd((g_info.env[i]) + index + 1, 1);
				else
					write(1, "\0", 1);
				write(1,"\"\n", 3);
			}
			else
			{
				char *tmp = g_info.env[i];
				ft_putendl_fd(tmp, 1);		
			}
				
			i++;
		}
	for (int i= 0; i < ft_str_count(g_info.env); i++)
	{
		printf("%d %s\n", i + 1, g_info.env[i]);
	}
	return (1);
}

int	msh_custom_unset(t_command *cmd)
{
	(void)cmd;
	return (1);
}

