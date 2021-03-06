/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:10 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 16:12:31 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_close_fd_redirects(t_redirect *tmp, t_command *cmd, int *fd_arr)
{
	int	fd_index;

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

int	msh_open(char *path, int type)
{
	if (type == REDIRECT)
	{
		return (open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU));
	}
	else if (type == D_REDIRECT)
	{
		return (open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU));
	}
	else if (type == R_REDIRECT)
	{
		return (open(path, O_RDONLY));
	}
	else
	{
		return (open(path, O_RDONLY, S_IRWXU));
	}
}

int	msh_define_redirects(int *fd_arr, t_command *cmd)
{
	int			fd_index;
	t_redirect	*tmp;

	fd_index = 0;
	tmp = NULL;
	if (cmd)
		tmp = cmd->redirects;
	while (tmp)
	{
		fd_index = msh_close_fd_redirects(tmp, cmd, fd_arr);
		fd_arr[fd_index] = msh_open(tmp->file, tmp->specials);
		if (fd_arr[fd_index] == -1)
		{
			perror(tmp->file);
			if (cmd->specials == DOUBLE_PIPE)
			{
				msh_save_error_code(errno);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	msh_redirects_fd(t_command *cmd)
{
	int		fd[2];
	int		status;

	if (cmd->redirects)
	{
		status = msh_define_redirects(fd, cmd);
		if (status)
			return (status);
		if (cmd->input)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		if (cmd->out)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
	}
	return (0);
}
