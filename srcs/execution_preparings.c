/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:06:05 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char *msh_recursion(char *dest, char *str, int *in , char *(fl)(char*, int*, char**))
{
	char	*tmp[2];
	int		i[2];
	t_arg	*tok;

	ft_bzero(i, sizeof(int) * 2);
	ft_bzero(tmp, sizeof(char *) * 2);
	i[0] = ft_index_of(str, c, 0);
	if (i[0] != -1)
	{

		//tmp[0] = msh_get_str_inside(str + i[0], i[1], 0); 
		// 1- можно вырезать 2- можно копировать для создания 3- можно заменить
		if (msh_is_token(tmp[0]))
			tmp[1] = msh_get_token_value(cmd, tmp[0])->value;
		i[1] = ft_strlen(tmp[1]) + ft_strlen(dest);
		dest = ft_realloc(dest, i[1]);
		dest = ft_strncat(dest, tmp[1], i[1]);
	}
	return (dest);
}

void msh_evaluate_all_tokens(t_command *cmd)
{
	int		i[6];
	char	copy[48];
	char	*buff[3];
	t_arg	*tok;

	ft_bzero(buff, sizeof(char *) * 3);
	ft_bzero(i, sizeof(int) * 6);
	while (cmd->args[i[0]])
	{
		i[1] = 0;
		i[2] = ft_index_of(cmd->args[i[0]], '%', 0);
		while (i[2] != -1)
		{
			buff[0] = msh_get_str_inside(cmd->args[i[0]] + i[2], "%", 0);
			if (msh_is_token(buff[0]))
			{
				if (ft_strlen(buff[0]) != ft_strlen(cmd->args[i[0]]))
				{
					i[3] = ft_strlen(buff[0]);
					i[4] = '%';
					buff[2] = msh_recursion(buff[2] , cmd->args[i[0]], i + 3);
					buff[1] = ft_strjoin(buff[0], buff[2]);
				}
				else
					buff[1] = msh_get_token_value(cmd, buff[0])->value;
				ft_strdel(&cmd->args[i[0]]);
				cmd->args[i[0]] = buff[1];
			}
			
		}
		i[0]++;
	}
}

/*
	int 	i[2];
	int 	count;
	char	copy[48];
	char	*buff[2];
	t_arg	*tok;

	ft_bzero(buff, sizeof(char *) * 2);
	ft_bzero(i, sizeof(int) * 2);
	while (cmd->args[i[0]])
	{
		i[1] = 0;
		while (cmd->args[i[0]][i[1]])
		{
			ft_bzero(copy, sizeof(char) * 48);
			while (cmd->args[i[0]][i[1]] && cmd->args[i[0]][i[1]] != '%')
			{
				copy[i[1]] = cmd->args[i[0]][i[1]];
				i[1]++;
			}
			if (msh_is_token(copy[i[0]]))
			{
				tok = msh_get_token_value(cmd, copy[i[0]]);
				if (!buff[0])
					buff[0] = ft_strdup(tok->value);
				else
				{
					buff[1] = ft_strjoin(buff[0], tok->value);
					ft_strdel(&buff[0]);
					buff[0] = buff[1];
				}
			}
			i[1]++;
		}
		ft_strdel(&cmd->args[i[0]]);
		cmd->args[i[0]] = buff[0];
		i[0]++;
	}
*/

int msh_make_path_relative(t_command *cmd)
{
	int res;
	char *tmp;

	res = 1;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if (!tmp)
	{
		msh_error_bash("command not found", cmd->args[0], 127);
		res = 0;
	}
	else if (ft_strncmp(tmp, cmd->args[0], ft_strlen(tmp)) != 0)
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}
