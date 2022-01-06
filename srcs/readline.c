/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:34 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:08:35 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_sigint_handler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void msh_readline(char *prefix, char **dest)
{
	char *line;

	line = readline(prefix);
	if (line)
		*dest = line;
	else
	{
		msh_struct_clear();
		exit(0);
	}
}
