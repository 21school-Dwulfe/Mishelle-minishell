/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:18 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:06:20 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int msh_execution_validation(t_command *cmd)
{
	DIR		*dir;
	char	*tmp[2];
	int		cases[2];
	
	ft_bzero(cases, sizeof(int) * 2);
	ft_bzero(tmp, sizeof(char) * 2);
	if (cmd->args[0][0] == '~')
	{
		tmp[0] = msh_get_env_by_key(g_info.env, "HOME");
		tmp[1] = ft_strjoin(tmp[0], cmd->args[0] + 1);
		ft_swap_strs(&cmd->args[0], &tmp[1]);
		ft_strdel(&tmp[1]);
	}
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
