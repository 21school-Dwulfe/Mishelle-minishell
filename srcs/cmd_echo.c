/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:17:33 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 19:18:30 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_cd_check_n(t_command *cmd, int *len, short *is_nl)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '-')
			break ;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j])
			break ;
		ft_strdel(&cmd->args[i]);
		cmd->args[i] = ft_strdup("-n");
		i++;
	}
	while (cmd->args[*len] && !ft_strcmp(cmd->args[*len], "-n"))
		(*len)++;
	if (cmd->num_args > 1 && !ft_strncmp(cmd->args[1], "-n", 3))
		(*is_nl)--;
}

char	*msh_custom_echo_buff(t_command *cmd, int *len)
{
	int		l[4];
	char	*tmp;

	tmp = NULL;
	ft_bzero(l, sizeof(int) * 4);
	if (cmd->num_args > 1 && !(*len == 2 && cmd->num_args == 2))
	{
		l[2] = *len;
		while (l[2] < cmd->num_args)
			l[0] += ft_strlen(cmd->args[l[2]++]);
		tmp = ft_calloc(sizeof(char), (l[0] + cmd->num_args - 2));
		while (*len < cmd->num_args)
		{
			ft_strncat(tmp, cmd->args[*len], (l[0] + cmd->num_args - 2));
			l[1] = ft_strlen(tmp);
			if (*len != cmd->num_args - 1)
				tmp[l[1]] = ' ';
			(*len)++;
		}
	}
	return (tmp);
}

int	msh_custom_echo(t_command *cmd)
{
	short	is_nl;
	int		len;
	char	*tmp;

	is_nl = 1;
	len = 1;
	msh_cd_check_n(cmd, &len, &is_nl);
	tmp = msh_custom_echo_buff(cmd, &len);
	if (tmp)
	{
		ft_putstr_fd(tmp, 1);
		ft_strdel(&tmp);
	}
	if (is_nl)
		ft_putstr_fd("\n", 1);
	msh_save_error_code(0);
	return (1);
}
