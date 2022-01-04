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
	DIR	*dir;
	int	cases[2];
	
	ft_bzero(cases, sizeof(int) * 2);
	cases[0] = ft_index_of(cmd->args[0], '/', 0);
	dir = opendir(cmd->args[0]);
	if (dir != NULL)
	{
		msh_error_bash("Is a directory", cmd->args[0], 126);
		closedir(dir);
		return (-1);
	}
	return (0);
}

int	msh_is_build(char *cmd)
{
	int		i;
	int		len[2];
	char	*ptr;
	char	*tmp;

	i = 0;
	ft_bzero(len, sizeof(int) * 2);
	while (i < 7)
	{
		len[0] = ft_strlen(g_info.f[i]);
		if (!ft_strncmp(cmd, g_info.f[i], len[0]))
			return (i + 1);
		ptr = ft_strrchr(cmd, '/');
		if (ptr)
			if (ft_strncmp(ptr + 1, "minishell", 10) == 0)
			{
				len[1] = ft_strlen(cmd) - ft_strlen(ptr + 1);
				tmp = ft_strndup_se(cmd, len[1], 0);
				if (strncmp(g_info.pwd, tmp, len[1]) == 0)
					return (i + 1);
			}
		i++;
	}
	return (-1);
}