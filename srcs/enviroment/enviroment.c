/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:05:51 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 17:51:12 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				temp[0] = ft_itoa(msh_read_error_code());
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
		new = ft_strjoin(tmp[1], tmp[0]);
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
	}
	else
		new = ft_strdup(new_var);
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
