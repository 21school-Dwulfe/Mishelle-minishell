/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:26 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/18 19:41:36 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_get_path(char *cmd_name, char **env)
{
	int		res;
	int		i[2];
	char	*tmp[4];
	char	**splited;

	ft_bzero(i, sizeof(int) * 2);
	ft_bzero(tmp, sizeof(char *) * 4);
	res = access(cmd_name, X_OK);
	if (res == -1 && ++i[1])
	{
		tmp[0] = msh_get_env_by_key(env, "PATH");
		splited = ft_split(tmp[0], ':');
		while (tmp[0] && splited[i[0]])
		{
			tmp[1] = ft_strjoin(splited[i[0]], "/");
			tmp[2] = ft_strjoin(tmp[1], cmd_name);
			ft_strdel(&tmp[1]);
			if (access(tmp[2], F_OK) == 0)
				break ;
			else
				ft_strdel(&tmp[2]);
			i[0]++;
		}
		ft_arrstr_del(splited, ft_str_count(splited));
		return (tmp[2]);
	}
	else
		return (ft_strdup(cmd_name));
}
