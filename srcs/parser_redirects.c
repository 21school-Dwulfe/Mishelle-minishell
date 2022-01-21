/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:48 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 17:17:04 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_cut_recursion(t_command *cmd, int i, char *c)
{
	int		j;

	j = 0;
	j = msh_first_redirect(cmd, &i, c);
	if (j == 1)
		msh_cut_recursion(cmd, i, c);
}

void	msh_cut_redirects(t_command *cmd, int i, char *c, int *in)
{
	char	*tp[2];

	ft_bzero(tp, sizeof(char *) * 2);
	if (cmd->args[i][0] != c[0])
	{
		tp[0] = ft_strndup_se(cmd->args[i], 0, c[0]);
		tp[1] = ft_strdup(cmd->args[i] + ft_index_of(cmd->args[i], c[0], 0));
		ft_strdel(&cmd->args[i]);
		cmd->args[i] = tp[1];
	}
	if (ft_strnstr(cmd->args[i], ">>", 3)
		&& ((in[1] != -1 && in[0] == -1)
			|| (in[1] != -1 && in[0] != -1 && in[1] < in[0])))
		ft_memset(c, '>', 2);
	else if (ft_strnstr(cmd->args[i], "<<", 3)
		&& ((in[0] != -1 && in[1] == -1)
			|| (in[0] != -1 && in[1] != -1 && in[0] < in[1])))
		ft_memset(c, '<', 2);
	msh_cut_recursion(cmd, i, c);
	if (tp[0])
		cmd->args[i] = tp[0];
}

static int	msh_redirects(t_command *cmd, char *c, int *in)
{
	int	i;

	i = 0;
	while (i < cmd->num_args)
	{
		ft_bzero(c, sizeof(char) * 4);
		in[0] = ft_index_of(cmd->args[i], '<', 0);
		in[1] = ft_index_of(cmd->args[i], '>', 0);
		if ((in[0] != -1 && in[1] == -1)
			|| (in[0] != -1 && in[1] != -1 && in[0] < in[1]))
			c[0] = '<';
		else if ((in[1] != -1 && in[0] == -1)
			|| (in[1] != -1 && in[0] != -1 && in[1] < in[0]))
			c[0] = '>';
		if (in[0] > -1 || in[1] > -1)
		{
			msh_cut_redirects(cmd, i, c, in);
			msh_replace_null_arg(cmd);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int	msh_cut_redirects_cmd(void)
{
	char		c[4];
	int			in[4];
	t_command	*cmd;

	cmd = g_info.cur_cmd;
	while (cmd)
	{
		if (msh_redirects(cmd, c, in) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
