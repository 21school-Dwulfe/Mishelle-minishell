/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:14:47 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 17:01:47 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_input_call(char **str, int *i)
{
	char	*line;
	char	*tmp;

	msh_readline(">", &line);
	tmp = *str;
	*str = ft_strjoin_se(tmp, line);
	ft_strdel(&line);
	ft_strdel(&tmp);
	if (i != NULL)
		*i = 0;
}

void	msh_stdin_regime(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		if (msh_validate_line(line))
			continue ;
		add_history(line);
		if (!msh_unclosed_quotes(&line, NULL, 0))
			msh_cmd(&line);
		ft_strdel(&line);
		msh_struct_clear();
		msh_init_global_cmd();
	}
}
