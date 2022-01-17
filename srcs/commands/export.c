/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:33 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int msh_modify_env_var(char **env, char *new_value)
{
	int		index_cmd;
	int		index_env;
	int 	len;
	char	*result;
	char	*tmp[4];

	len = 0;

	index_cmd = ft_index_of(new_value, '+', 0);
	if (index_cmd < 0)
	{
		result = ft_strdup(new_value);
	}
	else
	{
		index_cmd++;
		index_env = ft_index_of(*env, '=', 0);
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

int	msh_env_exist(char **env, char *argument)
{
	int		j;
	int		n[4];
	int		index;
	char	*tmp[2];

	j = 0;
	index = ft_index_of(argument, '+', 0);
	while (env[j])
	{
		ft_bzero(n, sizeof(int) * 4);
		while (env[j][n[0]] && env[j][n[0]] != '=')
			n[0]++;
		while (argument[n[1]] && argument[n[1]] != '=')
			n[1]++;
		tmp[0] = env[j];
		tmp[1] = ft_strndup_se(argument, 0, '=');
		if (!ft_strncmp(tmp[0], tmp[1], n[0]) && n[0] == n[1])
			n[3] = 1;
		if ((index > 1 && !ft_strncmp(env[j], tmp[1], index)))
			n[3] = 1;
		ft_strdel(&tmp[1]);
		if (n[3])
			return (j);
		j++;
	}
	return (-1);
}

char	*msh_get_env_by_key(char **env, char *argument)
{
	int j;
	int i;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (env[j])
	{
		i = msh_env_exist(env, argument);
		if (i > -1)
		{
			while (env[i][n] && env[i][n] != '=')
				n++;
			return((env[i]) + n + 1);
		}
		j++;
	}
	return (NULL);
}

int	msh_export_add(t_command	*cmd)
{
	int		i;
	int		arg_in_env;

	i = 1;
	while (i < cmd->num_args)
	{
		if (msh_export_invalid(cmd->args[i]))
			return (g_info.exit_code = msh_export_error(cmd->args[i]));
		arg_in_env = msh_env_exist(g_info.env, cmd->args[i]);
		if (arg_in_env != -1)
			msh_modify_env_var(&g_info.env[arg_in_env], cmd->args[i]);
		else
			g_info.env = msh_create_env_var(cmd->args[i]);
		i++;
	}
	msh_save_error_code(0);
	return (1);
}

int	msh_custom_export(t_command *cmd)
{
	int		i;
	int		index;
	char	**tmp;

	i = 1;
	if (cmd->num_args > 1)
		return(msh_export_add(cmd));
	else
	{
		tmp = msh_copy_env(g_info.env);
		ft_sort_params(ft_str_count(tmp), tmp);
		while (tmp[i])
		{
			ft_putstr_fd("declare -x ", 1);
			index = ft_index_of(tmp[i], '=', 0);
			if (index > -1)
			{
				write(1, tmp[i], index + 1);
				write(1,"\"", 1);
				if (ft_strlen((tmp[i]) + index + 1) > 0)
					ft_putstr_fd((tmp[i]) + index + 1, 1);
				else
					write(1, "\0", 1);
				write(1,"\"\n", 3);
			}
			else
				ft_putendl_fd(tmp[i], 1);		
			i++;
		}
		ft_arrstr_del(tmp, ft_str_count(tmp));
		msh_save_error_code(0);
	}
	return (1);
}
