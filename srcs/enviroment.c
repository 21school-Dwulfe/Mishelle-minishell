#include "../includes/main.h"

void	msh_replace_env_var_in_arg(char **arg_values, int index, char *new_value)
{
	int i;

	i = 0;
	while (new_value[i] != '=')
		i++;
	ft_strdel(&arg_values[index]);
	arg_values[index] = ft_strdup(new_value + (i + 1));
}

void	msh_evaluate_env_call_if_exist(t_command *cmd, char **env)
{
	int		i;
	int		j;
	int     k;
	char *temp;

	i = 0;
	while (i < cmd->num_args)
	{
		k = 0;
		temp = cmd->args[i];
		if (ft_strchr(temp, '$'))
			while (env[k])
			{
				j = 0;
				while (env[k][j] != '=')
					j++;
				if (!ft_strncmp(env[k], cmd->args[i], j))
				{
					msh_replace_env_var_in_arg(cmd->args, i, env[k]);
					return ;
				}
				k++;
			}
		i++;
	}
}

char	**msh_copy_env(char **array)
{
	int		l;
	char	*stop;
	char	**result;

	l = 1;
	stop = ft_strdup(array[0]);
	while (array[l] != 0)
		l++;
	result = malloc(sizeof(char *) * (l + 1));
	result[l] = 0;
	l = -1;
	while (array[++l])
		result[l] = ft_strdup(array[l]);
	free(stop);
	return (result);
}



char	**msh_create_env_var(char *new_var)
{
	int		length[2];
	int		i[4];
	char	*tmp[4];
	char	**result;
	char	*new;

	ft_bzero(length, sizeof(int) * 2);
	i[0] = ft_index_of(new_var, '+');
	i[1] = ft_index_of(new_var, '=');
	if (i[0] > -1)
	{
		tmp[0] = ft_strdup(new_var + i[1] + 1);
		tmp[1] = ft_strndup_se(new_var, 0, '=');
		tmp[1][i[1] - 1] = '=';
		tmp[1][i[1]] = '\0';
		//tmp[2] = ft_decorate(tmp[0], "\"", "\"");
		new = ft_strjoin(tmp[1], tmp[0]);
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
		//ft_strdel(&tmp[2]);
	}
	// else if (i[1] > -1)
	// {
	// 	tmp[0] = ft_strdup(new_var + i[1] + 1);
	// 	tmp[1] = ft_strndup_se(new_var, 0, '=');
	// //	if (ft_index_of(tmp[0], '\"') > -1)
	// 	//tmp[2] = ft_decorate(tmp[0], "\"", "\"");
	// 	new = ft_strjoin(tmp[1], tmp[2]);
	// 	ft_strdel(&tmp[0]);
	// 	ft_strdel(&tmp[1]);
	// //	ft_strdel(&tmp[2]);
	// }
	else
		new = new_var;
	while (g_info.env[length[1]])
		length[1]++;
	result = ft_realloc(g_info.env, sizeof(char *) * (length[1] + 2));
	result[length[1] + 1] = 0;
	result[length[1]] = new;
	return (result);
}

// int main(int argc, char **argv, char **env)
// {
// 	int i;
// 	t_command	*cmd;

// 	i = 0;
// 	cmd = malloc(sizeof(t_command));
// 	cmd->arguments = msh_copy_env(argv);
// 	cmd->number_args = argc;
// 	msh_evaluate_env_call_if_exist(cmd, env);
// 	i = 0;
// 	while (cmd->arguments[i])
// 	{
// 		printf("%s\n", cmd->arguments[i++]);
// 	}
//	free(cmd->arguments);
// 	free(cmd);
// 	return (0);
// }
