/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:25:41 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 19:38:41 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_env_exist(char **env, char *argument)
{
	int		j;
	int		n[4];
	int		index;
	char	*tmp[2];

	j = -1;
	index = ft_index_of(argument, '+', 0);
	while (env[++j])
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
	}
	return (-1);
}

char	*msh_get_env_by_key(char **env, char *argument)
{
	int	j;
	int	i;
	int	n;

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
			return ((env[i]) + n + 1);
		}
		j++;
	}
	return (NULL);
}

int	msh_custom_env(t_command *cmd)
{
	int	i;

	i = 0;
	(void)cmd;
	while (g_info.env[i])
	{
		if (ft_index_of(g_info.env[i], '=', 0) != -1)
			ft_putendl_fd(g_info.env[i], 1);
		i++;
	}
	msh_save_error_code(0);
	return (1);
}
