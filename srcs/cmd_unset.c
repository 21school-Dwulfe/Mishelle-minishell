/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:27:12 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 15:19:03 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_custom_unset(t_command *cmd)
{
	int		i;
	int		res;
	int		length;
	char	**args;
	char	**tmp;

	i = -1;
	args = cmd->args;
	length = ft_str_count(g_info.env);
	while (args[++i])
	{
		res = msh_env_exist(g_info.env, args[i]);
		if (res > -1)
		{
			ft_strdel(&g_info.env[res]);
			tmp = msh_concat_args(g_info.env, length);
			if (!tmp)
				return (msh_perror("malloc"));
			free(g_info.env);
			g_info.env = tmp;
			length = ft_str_count(g_info.env);
		}
	}
	msh_save_error_code(0);
	return (1);
}
