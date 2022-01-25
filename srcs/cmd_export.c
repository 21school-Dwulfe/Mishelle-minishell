/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:33 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 18:45:32 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_msh(int index_env, int index_cmd, char **env, char *new_value)
{
	int		len;
	char	*tmp[4];
	char	*result;

	len = 0;
	index_env = ft_index_of(*env, '=', 0);
	tmp[0] = ft_strdup(new_value + index_cmd + 1);
	if (index_env != -1)
		tmp[1] = ft_strdup(*env + index_env + 1);
	else
		tmp[1] = ft_strdup("");
	tmp[2] = ft_strjoin(tmp[1], tmp[0]);
	tmp[3] = ft_strndup_se(new_value, 0, '=');
	tmp[3][index_cmd - 1] = '=';
	result = ft_strjoin(tmp[3], tmp[2]);
	while (len < 4)
		ft_strdel(&tmp[len++]);
	return (result);
}

int	msh_modify_env_var(char **env, char *new_value)
{
	int		index_cmd;
	int		index_env;
	char	*result;

	index_env = 0;
	index_cmd = ft_index_of(new_value, '+', 0);
	if (index_cmd < 0)
		result = ft_strndup_se(new_value, 0, 0);
	else
	{
		index_cmd++;
		result = msh_msh(index_env, index_cmd, env, new_value);
	}
	ft_strdel(env);
	*env = result;
	return (1);
}

int	msh_export_add(t_command	*cmd)
{
	int		i;
	int		arg_in_env;

	i = 1;
	while (i < cmd->n_args)
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

void	msh_print_export(int i, char **tmp)
{
	int		index;

	ft_putstr_fd("declare -x ", 1);
	index = ft_index_of(tmp[i], '=', 0);
	if (index > -1)
	{
		write(2, tmp[i], index + 1);
		write(2, "\"", 1);
		if (ft_strlen((tmp[i]) + index + 1) > 0)
			ft_putstr_fd((tmp[i]) + index + 1, 1);
		else
			write(2, "\0", 1);
		write(2, "\"\n", 3);
	}
	else
		ft_putendl_fd(tmp[i], 1);
}

int	msh_custom_export(t_command *cmd)
{
	int		i;
	char	**tmp;

	i = 1;
	if (cmd->n_args > 1)
		return (msh_export_add(cmd));
	else
	{
		tmp = msh_copy_env(g_info.env);
		ft_sort_params(ft_str_count(tmp), tmp);
		while (tmp[i])
		{
			msh_print_export(i, tmp);
			i++;
		}
		ft_arrstr_del(tmp, ft_str_count(tmp));
		msh_save_error_code(0);
	}
	return (1);
}
