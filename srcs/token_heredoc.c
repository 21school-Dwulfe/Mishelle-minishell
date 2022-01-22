/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:55:51 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/22 17:03:04 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_heredoc_value_to_name(char *value)
{
	int		i;
	char	*tmp;

	i = 2;
	while (value[i] && value[i] == ' ')
		i++;
	tmp = value;
	value = ft_strdup(tmp + i);
	ft_strdel(&tmp);
	return (value);
}

int	msh_convert_heredoc(t_command *cmd, char *value, char *name, int sp)
{
	int	len;

	len = ft_strlen(value);
	name = msh_heredoc_value_to_name(value);
	msh_add_redirect(&cmd->redirects, name, sp);
	rl_clear_history();
	msh_heredoc_input(name);
	return (len);
}
