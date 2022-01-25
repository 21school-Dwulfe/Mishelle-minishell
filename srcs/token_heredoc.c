/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:55:51 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 18:11:37 by dwulfe           ###   ########.fr       */
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

void	msh_heredoc_input(char *name)
{
	int		i[3];
	char	*ptr[3];
	int		fd;

	i[0] = ft_strlen(name);
	i[1] = 1;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
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
	close(fd);
}
