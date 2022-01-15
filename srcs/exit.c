/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:26 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:06:27 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_read_error_code(void)
{
	int res;
	
	res = g_info.exit_code;
	return (res);
}

void	msh_save_error_code(int code)
{
	printf("save %d", code);
	g_info.exit_code = code;
}

void	msh_custom_exit(t_command *cmd)
{
	(void)cmd;
	if (cmd->num_args > 2)
		exit(1);
	else if (cmd->num_args == 1)
		exit(0);
	else
		exit(ft_atoi(cmd->args[1]));
}