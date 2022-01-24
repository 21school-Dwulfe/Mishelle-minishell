/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:55:51 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 00:07:05 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*msh_heredoc_value_to_name(char *value)
{
	int		i;

	i = 0;
	while (value[i] == value[0])
		i++;
	while (value[i] && value[i] == ' ')
		i++;
	return (ft_strdup(value + i));
}

//msh_add_token(cmd, msh_create_token(NULL, NULL, g_info.num_token++, sp));
int	msh_convert_heredoc(t_command *cmd, char *value, char *name, int sp)
{
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(value);
	while (value[j] && ft_isdigit(value[j]))
		j++;
	name = msh_heredoc_value_to_name(value);
	msh_push_redirect(&cmd->redirects, name, sp);
	if (value[j] - value[0] > 0)
		msh_last_redirect(cmd)->std->in = ft_atoi(value);
	signal(SIGINT, SIG_IGN);
	msh_heredoc_input(name);
	signal(SIGINT, msh_sigint_handler);
	return (len);
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
