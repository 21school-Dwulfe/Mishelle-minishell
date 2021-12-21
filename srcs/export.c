#include "../includes/main.h"

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
int	msh_env_str(char **env, char *argument)
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

char	*msh_env_get_if_exist(char **env, char *argument)
{
	int j;
	int i;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (env[j])
	{
		i = msh_env_str(env, argument);
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
