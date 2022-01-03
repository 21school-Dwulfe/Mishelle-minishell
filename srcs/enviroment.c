#include "../includes/main.h"

// int	msh_dollar_error_case(t_command *cmd, char *tmp, int j)
// {
// 	int		i[3];
// 	char	*temp[6];

// 	ft_bzero(i, sizeof(int) * 3);
// 	ft_bzero(temp, sizeof(char *) * 6);
// 	temp[0] = cmd->args[j];
// 	temp[2] = tmp;
// 	temp[3] = ft_itoa(msh_read_error_code());
// 	temp[4] = ft_strjoin(temp[3], temp[1] + 2);
// 	if (temp[0][0] != '$')
// 	{
// 		temp[5] = ft_strndup_se(temp[0], 0, '$');
// 		temp[1] = ft_strjoin(temp[5], temp[4]);
// 		i[2] = 6;
// 	}
// 	else
// 	{
// 		temp[1] = ft_strdup(temp[4]);
// 		i[2] = 5;
// 	}
// 	cmd->args[j] = temp[1];
// 	while (1 != --i[2])
// 		ft_strdel(&temp[i[2]]);
// 	ft_strdel(&temp[0]);
// 	return (2);
// }

// int	msh_dollar_common_case(t_command *cmd, char *tmp, char **env, int *k)
// {
// 	int		i[3];
// 	char	*temp[6];

// 	ft_bzero(temp, sizeof(char) * 6);
// 	ft_bzero(i, sizeof(int) * 3);
// 	temp[1] = tmp;
// 	temp[2] = msh_get_env_by_key(env, temp[1] + 1);
// 	if (temp[2])
// 	{
// 		if (i[1] != 0)
// 		{
// 			if (k[2] == 1)
// 			{
// 				temp[3] = ft_strndup_se(temp[0], 0, '$');
// 				temp[4] = ft_strjoin(temp[3], temp[2]);
// 			}
// 			if (k[1] == 1)
// 				cmd->args[k[0]] = temp[4];
// 			else
// 			{
// 				temp[5] = ft_strjoin(cmd->args[k[0]], temp[4]);
// 				ft_strdel(&cmd->args[k[0]]);
// 				cmd->args[k[0]] = temp[5];
// 			}
// 			i[2] = ft_strlen(temp[1]);
// 			ft_strdel(&temp[3]);
// 		}
// 		else
// 			cmd->args[k[0]] = ft_strdup(temp[2]);
// 	}
// 	else
// 	{
// 		ft_memset(temp[1], '\0', ft_strlen(temp[1]));
// 		temp[1] = temp[0];
// 		cmd->args[k[0]] = msh_concat_str(temp[1], ft_strlen(temp[0]), NULL);
// 	}
// 	return (ft_strlen(temp[1]));
// }

// void	msh_evaluate_env_call_if_exist(t_command *cmd, char **env)
// {
// 	int		i[5];
// 	int		k[3];
// 	char	*temp[6];
// 	int 	j;
// 	int 	count_dollars;

// 	j = 0;
// 	ft_bzero(i, sizeof(int) * 5);
// 	ft_bzero(temp, sizeof(char *) * 6);
// 	while (i[0] < cmd->num_args)
// 	{
// 		j = 0;
// 		temp[0] = cmd->args[i[0]];
// 		count_dollars = ft_ch_count(temp[0], '$');
// 		while (j < count_dollars)
// 		{
// 			temp[1] = ft_strchr(temp[0], '$');
// 			i[1] = ft_index_of(temp[0], '$');
// 			if (temp[1] && temp[1][1] != '?' &&  temp[0][0] != '\'')// need to set flag
// 			{
// 				k[0] = i[0];
// 				k[1] = count_dollars;
// 				k[2] = j;
// 				i[4] = msh_dollar_common_case(cmd, temp[1], env, k);
				
// 			}
// 			else if (temp[1] && temp[1][1] == '?' && temp[0][0] != '\'')
// 			{
// 				i[4] = msh_dollar_error_case(cmd, temp[1], i[0]);
// 			}
// 			temp[0] = temp[0] + i[4];
// 			j++;
// 		}
// 		i[0]++;
// 	}
// }

char	*msh_dollar_error_case(char **args, char *tmp, int j)
{
	int		i[3];
	char	*temp[6];

	ft_bzero(i, sizeof(int) * 3);
	ft_bzero(temp, sizeof(char *) * 6);
	temp[0] = args[j];
	temp[2] = tmp;
	temp[3] = ft_itoa(msh_read_error_code());
	temp[4] = ft_strjoin(temp[3], temp[1] + 2);
	if (temp[0][0] != '$')
	{
		temp[5] = ft_strndup_se(temp[0], 0, '$');
		temp[1] = ft_strjoin(temp[5], temp[4]);
		i[2] = 6;
	}
	else
	{
		temp[1] = ft_strdup(temp[4]);
		i[2] = 5;
	}
	args[j] = temp[1];
	while (1 != --i[2])
		ft_strdel(&temp[i[2]]);
	ft_strdel(&temp[0]);
	return (temp[1]);
}

char	*msh_evaluate_env_arg(char *arg, char **env)
{
	int		length[2];
	int		size;
	char	*val[3];
	char	*tmp;

	tmp = arg;
	ft_bzero(length, sizeof(int) * 2);
	while (tmp[length[0]] != '$')
		length[0]++;
	tmp = tmp + length[0] + 1;
	while (tmp)
	{
		if (!ft_isalnum(*tmp) && *tmp != '_')
			break;
		length[1]++;
		tmp++;
	}
	val[0] = ft_strndup(arg + length[0] + 1, length[1]);
	size = ft_strlen(arg);
	val[1] = msh_get_env_by_key(env, val[0]);
	ft_memset(arg + length[0], '\0', ft_strlen(val[0]) + 1);
	ft_strdel(&val[0]);
	arg = msh_concat_str(arg, size, val[1]);
	return (arg);
}

/**
 * @brief 
 * 
 * @param args 
 * @param env 
 * @return int 
 */
int	msh_evaluate_env_if_exist(char **args, char **env)
{
	int		i;
	int 	j;
	int 	count_dollars;
	char	*temp[2];

	j = 0;
	i = 0;
	ft_bzero(temp, sizeof(char *) * 2);
	while (args[i])
	{
		j = 0;
		temp[0] = args[i];
		count_dollars = ft_ch_count(temp[0], '$');
		while (j < count_dollars)
		{
			if (temp[0] && temp[0][1] != '?')
				temp[0] = msh_evaluate_env_arg(temp[0], env);
			else if (temp[0] && temp[0][1] == '?')
				temp[0] = msh_dollar_error_case(args, temp[0], i);
			j++;
			ft_strdel(&args[i]);
			args[i] = temp[0];
		}
		i++;
	}
	return (ft_strlen(temp[0]));
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
	int		length[3];
	int		i[4];
	char	*tmp[4];
	char	**result;
	char	*new;

	ft_bzero(length, sizeof(int) * 3);
	i[0] = ft_index_of(new_var, '+', 0);
	i[1] = ft_index_of(new_var, '=', 0);
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
	result = ft_calloc((length[1] + 2), sizeof(char *));
	while (g_info.env[length[2]])
	{
		result[length[2]] = ft_strdup(g_info.env[length[2]]);
		length[2]++;
	}
	result[length[1]] = new;
	result[length[1] + 1] = (void *)0;
	ft_arrstr_del(g_info.env, length[1]);
	return (result);
}

// int main(void)
// {
// 	char *str = "str\0\0\0hr";
// 	char *new = msh_concat_str(str, 8);
// 	printf("%s\n", new);
// 	return (0);
// }

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

