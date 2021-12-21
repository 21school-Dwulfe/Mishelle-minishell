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
	if (cmd->num_args > 1)
	{
		tmp[0] = ft_strchr(cmd->args[1], '-');
		if (tmp[0] && *(tmp[0] + 1) == 'n' && (--is_nl == 0))
			len = 2;
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

// int msh_modify_env_var(char **env, char *new_value)
// {
// 	int		index_cmd;
// 	int		index_env;
// 	int 	len;
// 	char	*result;
// 	char	*tmp[6];

// 	len = 0;
// 	index_cmd = ft_index_of(new_value, '+');
// 	if (index_cmd < 0)
// 		index_cmd = ft_index_of(new_value, '=');
// 	else
// 		index_cmd++;
// 	tmp[0] = ft_strdup(new_value + index_cmd + 1);
// 	index_env = ft_index_of(*env, '=');
// 	tmp[1] = ft_strdup(*env + index_env + 1);
// 	tmp[2] = ft_strtrim(tmp[0], "");
// 	tmp[3] = ft_strtrim(tmp[1], "\"");
// 	tmp[4] = ft_strjoin(tmp[3], tmp[2]);
// 	result = ft_decorate(tmp[4], "\"", "\"");
// 	ft_strdel(env);
// 	*env = result;
// 	while (len < 6)
// 	{
// 		ft_strdel(&tmp[len]);
// 		len++;
// 	}
// 	return (1);
// }

int msh_modify_env_var(char **env, char *new_value)
{
	int		index_cmd;
	int		index_env;
	int 	len;
	char	*result;
	char	*tmp[4];

	len = 0;

	index_cmd = ft_index_of(new_value, '+');
	if (index_cmd < 0)
		result = new_value;
	else
	{
		index_cmd++;
		index_env = ft_index_of(*env, '=');
		tmp[0] = ft_strdup(new_value + index_cmd + 1);
		if (index_env != - 1)
			tmp[1] = ft_strdup(*env + index_env + 1);
		else
			tmp[1] = ft_strdup("");
		tmp[2] = ft_strjoin(tmp[1], tmp[0]);
		tmp[3] = ft_strndup_se(new_value, 0, '=');
		tmp[3][index_cmd - 1] = '=';
		result = ft_strjoin(tmp[3], tmp[2]);
		while (len < 4)
		{
			ft_strdel(&tmp[len]);
			len++;
		}
	}
	ft_strdel(env);
	*env = result;
	
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
	int		j;
	int		n[4];
	int		index;
	char	*tmp[2];

	j = 0;
	index = ft_index_of(argument, '+');
	while (env[j])
	{
		ft_bzero(n, sizeof(int) * 4);
		while (env[j][n[0]] && env[j][n[0]] != '=')
			n[0]++;
		while (argument[n[1]] && argument[n[1]] != '=')
			n[1]++;
		tmp[0] = env[j];
		tmp[1] = ft_strndup_se(argument, 0, '=');
		if (!ft_strncmp(tmp[0], tmp[1], n[0]))
			n[3] = 1;
		if ((index > 1 && !ft_strncmp(env[j], tmp[1], index)))
			n[3] = 1;
		ft_strdel(&tmp[1]);
		if (n[3])
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
			return((env[i]) + n + 1);
		}
		j++;
	}
	return (0);
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
		arg_in_env = msh_check_if_exist(g_info.env, cmd->args[i]);
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
				ft_putendl_fd(g_info.env[i], 1);		
			i++;
		}
	return (1);
}

int	msh_custom_unset(t_command *cmd)
{
	(void)cmd;
	return (1);
}

