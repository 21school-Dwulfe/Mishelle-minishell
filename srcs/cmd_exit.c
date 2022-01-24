/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:26 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 18:18:01 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_read_error_code(void)
{
	int	res;

	res = g_info.exit_code;
	return (res);
}

void	msh_save_error_code(int code)
{
	g_info.exit_code = code;
}

void	msh_custom_exit(t_command *cmd)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	if (cmd->n_args == 1)
		exit(g_info.exit_code);
	ft_putendl_fd(cmd->args[0], 1);
	while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
		i++;
	if ((int)ft_strlen(cmd->args[1]) != i)
	{
		len = ft_strlen(cmd->args[0]) + ft_strlen(cmd->args[1]) + 3;
		tmp = ft_calloc(len, sizeof(char));
		tmp = ft_strcpy(tmp, cmd->args[0]);
		tmp = ft_strncat(tmp, ": ", len);
		tmp = ft_strncat(tmp, cmd->args[1], len);
		exit(msh_error_bash("numeric argument required", tmp, 255));
	}
	else if (cmd->n_args > 2)
		exit(msh_error_bash("too many arguments", cmd->args[0], 1));
	else
		exit (ft_atoi(cmd->args[1]));
}
