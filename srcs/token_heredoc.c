/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:55:51 by dwulfe            #+#    #+#             */
/*   Updated: 2022/03/03 19:51:03 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_convert_to_redirect(t_command *cmd, char *value, int sp)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!cmd || !value)
		return ;
	while (value[j] && ft_isdigit(value[j]))
		j++;
	while (value[i] == value[0])
		i++;
	while (value[i] && value[i] == ' ')
		i++;
	msh_push_redirect(&cmd->redirects, ft_strdup(value + i + j), sp);
	if (value[j] - value[0] > 0)
		msh_last_redirect(cmd)->std->in = ft_atoi(value);
}

void	msh_heredoc_fork(int *i, int fd, char *name, char **ptr)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		//signal(SIGINT, sig_hr);
		while (i[1])
		{
			i[2] = msh_readline(">", &ptr[0], 0);
			if (!i[2])
				break ;
			ptr[2] = ft_strnstr(ptr[0], name, i[0]);
			if (ptr[2])
				break ;
			else
			{
				write(fd, ptr[0], ft_strlen(ptr[0]));
				write(fd, "\n", 1);
				ft_strdel(&ptr[0]);
			}
		}
		if (i[2])
			ft_strdel(&ptr[0]);
		exit(0);
	}
}

void	msh_heredoc_input(char *name)
{
	int		fd;
	int		status;
	char	*ptr[3];
	int		i[3];

	i[0] = ft_strlen(name);
	i[1] = 1;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd == -1)
		msh_perror(name);
	msh_heredoc_fork(i, fd, name, ptr);
	waitpid(0, &status, 0);
	if (WIFSIGNALED(status) > 0)
	{
		if (WTERMSIG(status) == 2)
			write(1, "\n", 1);
	}
	signal(SIGINT, SIG_IGN);
	close(fd);
}
