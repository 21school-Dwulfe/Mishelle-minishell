/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:18 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_tilda(char **arg)
{
	char	*tmp[2];

	ft_bzero(tmp, sizeof(char) * 2);
	if (arg && arg[0] == '~')
	{
		tmp[0] = msh_get_env_by_key(g_info.env, "HOME");
		tmp[1] = ft_strjoin(tmp[0], arg + 1);
		ft_swap_strs(arg, &tmp[1]);
		ft_strdel(&tmp[1]);
	}
}

int msh_execution_validation(t_command *cmd)
{
	DIR		*dir;
	int		cases[2];
	
	if (!cmd->args || !cmd->num_args)
		return (0);
	ft_bzero(cases, sizeof(int) * 2);
	cases[0] = ft_index_of(cmd->args[0], '/', 0);
	dir = opendir(cmd->args[0]);
	if (dir != NULL)
	{
		closedir(dir);
		return (msh_error_bash("Is a directory", cmd->args[0], 126));
	}
	if (cases[0] > -1)
		return (msh_error_bash("No such file or directory", cmd->args[0], 127));
	return (0);
}

int	msh_is_build(char *cmd)
{
	int		i;
	int		len;

	i = 0;
	if (!cmd)
		return (-1);
	while (i < 8)
	{
		len = ft_strlen(g_info.f[i]);
		if (!ft_strncmp(cmd, g_info.f[i], len + 1))
			return (i + 1);	
		i++;
	}
	return (-1);
}
