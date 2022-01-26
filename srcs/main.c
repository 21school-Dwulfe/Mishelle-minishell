/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:53 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/26 18:05:15 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh(t_command *cmd, int *in_out_s, int *fd_pipe, int *counter)
{
	int	status;

	if (msh_buildin_excutor(cmd) == 0)
	{
		if (msh_pipes(cmd, fd_pipe) > -1)
			(*counter)++;
		else
			return (-1);
		msh_func(cmd, in_out_s, g_info.env, fd_pipe);
	}
	status = msh_d_amp_d_pipe(cmd);
	return (status);
}

int	msh_executor(t_command *cmd, int *in_out_s, int *counter)
{
	int		fd_pipe[2];
	int		status;

	while (cmd)
	{
		status = (msh_preparings(cmd) | msh_redirects_fd(cmd));
		if (status == 1)
			break ;
		else if (status == 2)
		{
			cmd = cmd->next;
			continue ;
		}
		status = msh(cmd, in_out_s, fd_pipe, counter);
		if (status == 1)
			break ;
		else if (status == 2)
			cmd = cmd->next;
		cmd = cmd->next;
		if ((cmd && !cmd->piped) || !cmd)
			dup2(in_out_s[1], 1);
	}
	return (*counter);
}

void	msh_cmd(char **line)
{
	int		in_out_s[2];
	int		counter;

	counter = 0;
	if (msh_parse(line) == -1)
		return ;
	if (msh_cut_redirects_cmd() == -1)
		return ;
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	msh_executor(g_info.cur_cmd, in_out_s, &counter);
	dup2(in_out_s[1], 1);
	close(in_out_s[1]);
	dup2(in_out_s[0], 0);
	close(in_out_s[0]);
	while (counter-- > 0)
		msh_wait_pid(0);
	signal(SIGINT, msh_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	msh_argv_regime(char **argv, int argc)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	line = NULL;
	while (i < argc)
	{
		line = ft_strjoin_se(line, argv[i]);
		tmp = line;
		line = ft_strjoin(tmp, " ");
		ft_putstr_fd(line, 1);
		ft_strdel(&tmp);
		i++;
	}
	if (msh_validate_line(line))
		return ;
	if (!msh_unclosed_quotes(&line, NULL, 0))
		msh_cmd(&line);
	ft_strdel(&line);
	msh_struct_clear();
}

int	main(int argc, char **argv, char **env)
{
	int	regime;

	msh_config(argc, argv, env, &regime);
	if (regime)
		msh_argv_regime(argv + 1, argc - 1);
	else
		msh_stdin_regime();
	return (0);
}
