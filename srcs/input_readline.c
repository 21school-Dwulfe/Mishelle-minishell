/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:34 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 13:53:19 by dwulfe           ###   ########.fr       */
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

int	msh_readline(char *prefix, char **dest, int regime)
{
	char	*line;

	line = readline(prefix);
	if (line)
		*dest = line;
	else if (regime)
	{
		msh_struct_clear();
		exit(0);
	}
	if (!line)
		return (regime);
	else
		return (1);
}
