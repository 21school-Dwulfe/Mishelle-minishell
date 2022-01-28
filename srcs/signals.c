/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:03:46 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 22:22:59 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		exit(2);
	}
	if (sig == SIGQUIT)
	{
		exit(3);
	}
}

void	msh_define_subshell_signals(char *shell_start, char *shell_current)
{
	if (!ft_strncmp(shell_start, shell_current, ft_strlen(shell_current)))
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, msh_child_sig);
	signal(SIGINT, msh_sigint_handler);
}

void	msh_sigignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
