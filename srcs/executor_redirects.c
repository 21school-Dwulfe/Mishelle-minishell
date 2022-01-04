/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:10 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:06:11 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int msh_redirects_fd(t_redirect *tmp, t_command *cmd, int *fd_arr)
{
    int			fd_index;

    if (tmp->specials == 5 || tmp->specials == 7)
    {
        if (cmd->input)
            close(fd_arr[0]);
        cmd->input = tmp;
        fd_index = 0;
    }
    if (tmp->specials == 4 || tmp->specials == 6)
    {
        if (cmd->out)
            close(fd_arr[1]);
        cmd->out = tmp;
        fd_index = 1;
    }
    return (fd_index);
}

int	msh_custom_redirect(int *fd_arr, t_command *cmd)
{
	int			fd_index;
	t_redirect	*tmp;

	fd_index = 0;
	tmp = NULL;
	if (cmd)
		tmp = cmd->redirects;
	while (tmp)
	{
		fd_index = msh_redirects_fd(tmp, cmd, fd_arr);
		fd_arr[fd_index] = msh_open(tmp->file, tmp->specials);
		if (fd_arr[fd_index] == -1)
		{
			perror(tmp->file);
			return (1);
		}
		tmp = tmp->next;
	}
	return(0);
}
