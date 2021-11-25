#include "../includes/main.h"

void	msh_replace_env_var_in_arg(char **arg_values, int index, char *new_value)
{
	int i;

	i = 0;
	while (new_value[i] != '=')
		i++;
	ft_strdel(arg_values[index]);
	arg_values[index] = ft_strdup(new_value + (i + 1));
}

void	msh_evaluate_env_call_if_exist(t_command *cmd, char **env)
{
	int		i;
	int		j;
	int     k;

	i = 0;
	while (i < cmd->number_args)
	{
		k = 0;
		while (env[k])
		{
			j = 0;
			while (env[k][j] != '=')
				j++;
			if (!ft_strncmp(env[k], cmd->arguments[i], j))
			{
				msh_replace_env_var_in_arg(cmd->arguments, i, env[k]);
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
	char	**result;

	l = 0;
	while (array[l])
		l++;
	result = malloc(sizeof(char *) * (l + 1));
	result[l] = 0;
	l = -1;
	while (array[++l])
		result[l] = ft_strdup(array[l]);
	return (result);
}

void	*ft_realloc(void *memory, size_t size)
{
	int		i;
	void	*result;

	result = malloc(size);
	if (result)
	{
		ft_bzero(result, size);
		while (((unsigned char *)memory)[i])
			((unsigned char *)result)[i] = ((unsigned char *)memory)[i++];
		ft_delptr(memory);
		return (result);
	}
	return (NULL);
}

char	**msh_create_env_var(char *new_var)
{
	int		length;
	char **result;

	while (g_info.env[length])
		length++;
	result = ft_realloc(g_info.env, sizeof(char *) * (length + 1));
	result[length] = new_var;
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
