#include "../includes/main.h"

int	msh_custom_pwd(t_command *cmd)
{
	char str[512];

	(void)cmd;
	getcwd(str, sizeof(str));
	printf("%s\n", str);
	return (1);
}
int	msh_custom_exit(t_command *cmd)
{
	(void)cmd;
	exit(1);
	return (1);
}

char	*msh_add_space(int len, char *tmp, t_command *cmd)
{
	if (len < cmd->num_args)
	{
		tmp = ft_realloc(tmp, ft_strlen(tmp) + 2);
		tmp[ft_strlen(tmp)] = ' ';
	}
	return(tmp);
}

int	msh_custom_echo(t_command *cmd)
{
	short	is_nl;
	int		len;
	char	*c;
	char	*tmp[2];

	is_nl = 1;
	len = 1;
	c = NULL;
	if (cmd->num_args > 1)
		c = ft_strchr(cmd->args[1], '-');
	if (c && ft_strlen(c) == 2 && *(c + 1) == 'n' && (--is_nl == 0))
		len = 2;
	tmp[0] = cmd->args[len];
	while (cmd->args[++len])
	{
		tmp[1] = msh_add_space(len, tmp[0], cmd);
		tmp[0] = ft_strjoin(tmp[1], cmd->args[len++]);
		ft_strdel(&tmp[1]);
	}
	if (is_nl)
		ft_putendl_fd(tmp[0], 1);
	else
		ft_putstr_fd(tmp[0], 1);
	ft_strdel(&tmp[0]);
	return (1);
}

int	msh_custom_env(t_command *cmd)
{
	(void)cmd;
	return (1);
}

int	msh_custom_cd(t_command *cmd)
{
	// int i;

	// i = 0;
	// while ()
	// {

	// }
	chdir(cmd->args[0]);
	return (1);
}

int msh_modify_env_var(char **env, char *new_value)
{
	ft_strdel(env);
	*env = new_value;
	return (1);
}

/**
 * @brief 
 * 
 * @param arguments an array of arguments to look for in a variable environment
 * @param env variable environment
 * @return int returns 1 if true 0 if false
 */
int	msh_check_if_exist(char **env, char *argument)
{
	int j;
	int n;
	int	index;

	j = 0;
	index = ft_index_of(argument, '+');
	while (env[j])
	{
		n = 0;
		while(env[j][n] && env[j][n] != '=')
			n++;
		if (ft_strncmp(env[j], argument, n - 1) == 0)
			return (j);
		if (index > 0 && ft_strncmp(env[j], argument, index + 1))
			return (j);
		j++;
	}
	return (0);
}

char	*msh_get_if_exist(char **env, char *argument)
{
	int j;
	int i;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (env[j])
	{
		i = msh_check_if_exist(env, argument);
		if (i)
		{
			while (env[i][n] && env[i][n] != '=')
				n++;
			return((env[i]) + n);
		}
		j++;
	}
	return (0);
}

void	msh_export_add(t_command	*cmd)
{
	int		i;
	int		arg_in_env;
	char	*tmp[2];
	int		index;

	i = 1;
	while (i < cmd->num_args)
	{
		if (msh_export_invalid(cmd->args[i]))
		{
			msh_export_error(cmd->args[i]);
			break ;
		}
		arg_in_env = msh_check_if_exist(g_info.env, cmd->args[i]);
		index = ft_index_of(cmd->args[i], '+');
		if (index > -1)
		{
			tmp[0] = ft_strdup((g_info.env[arg_in_env]) + ft_index_of(g_info.env[arg_in_env], '=') + 1);
			tmp[1] = ft_strjoin_se(tmp[0], (g_info.env[arg_in_env]) + index + 1);
			ft_strdel(&tmp[0]);
			ft_strdel(&cmd->args[i]);
			cmd->args[i] = tmp[1];
		}
		if (arg_in_env)
			msh_modify_env_var(&g_info.env[arg_in_env], cmd->args[i]);
		else
			g_info.env = msh_create_env_var(cmd->args[i]);
	}

}

// -n -p -f
int	msh_custom_export(t_command *cmd)
{
	int		i;

	i = 1;
	if (cmd->num_args > 1)
		msh_export_add(cmd);
	else
		while (g_info.env[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(g_info.env[i], 1);
			i++;
		}
	return (1);
}

int	msh_custom_unset(t_command *cmd)
{
	(void)cmd;
	return (1);
}

