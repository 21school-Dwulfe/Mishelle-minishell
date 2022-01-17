// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/01/04 20:04:25 by dwulfe            #+#    #+#             */
// /*   Updated: 2022/01/08 21:22:37 by dwulfe           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/main.h"

// int	msh_subshell(t_command *cmd)
// {

// }

void	msh_cmd(char **line)
{
	int	in_out_s[2];
	int counter;

	if (msh_parse(line) == -1)
		return ;
	if (msh_cut_redirects_cmd() == -1)
		return ;
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	counter = msh_executor(g_info.cur_cmd, g_info.env, in_out_s);
	close(in_out_s[1]);
	dup2(in_out_s[0], 0);
	close(in_out_s[0]);
	while (counter-- > 0)
		msh_wait_pid(-1);
	signal(SIGINT, msh_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}