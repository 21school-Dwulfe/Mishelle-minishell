/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects_recursion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:41 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/17 16:46:56 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	msh_set_specials(char *c, char *src, int *rr)
{
	char	ch[2];

	ch[0] = '<';
	ch[1] = '>';
	ft_bzero(c, sizeof(char) * ft_strlen(c));
	if (src[rr[rr[4]] + 1] == src[rr[rr[4]]])
		ft_memset(c, ch[rr[4]], 2);
	else
		c[0] = ch[rr[4]];
}

static int msh_get_specials(char *c)
{
	int index;
	
	index = ft_strlen(c);
	if (index == 2 && c[0] == '<')
		return (RD_REDIRECT);
	if (index == 1 && c[0] == '<')
		return (R_REDIRECT);
	if (index == 2 && c[0] == '>')
		return (D_REDIRECT);
	if (index == 1 && c[0] == '>')
		return (REDIRECT);
	return (0);
}

static int	msh_prefix_redirect(t_command *cmd, int *i, char *c, int *rr)
{
	if (ft_strcmp(cmd->args[*i], c) == 0)
	{
		ft_strdel(&cmd->args[*i]);
		(*i)++;
		return (1);
	}
	msh_add_redirect(&cmd->redirects, ft_strdup(cmd->args[*i] + rr[2]), rr[3]);
	ft_strdel(&cmd->args[*i]);
	return (0);
}

static int	msh_postfix_redirect(t_command *cmd, int *i, char *c, int *rr)
{
	char	*dest;
	char	*hren;

	dest = ft_strndup_se(cmd->args[*i] + rr[2], rr[rr[4]], 0);
	msh_add_redirect(&cmd->redirects, dest, rr[3]);
	msh_set_specials(c, cmd->args[*i] + rr[2], rr);
	hren = ft_strdup(cmd->args[*i] + rr[2] + ft_strlen(dest));
	ft_strdel(&cmd->args[*i]);
	cmd->args[*i] = hren;
	if (ft_strcmp(cmd->args[*i], c) == 0)
	{
		ft_strdel(&cmd->args[*i]);
		(*i)++;
	}
	return (1);
}

int	msh_first_redirect(t_command *cmd, int *i, char *c)
{
	int		rr[5];

	ft_bzero(rr, sizeof(int) * 5);
	while (cmd->args[*i][rr[2]] == c[0])
		rr[2]++;
	rr[0] = ft_index_of(cmd->args[*i] + rr[2], '<', 1);
	rr[1] = ft_index_of(cmd->args[*i] + rr[2], '>', 1);
	if (rr[0] < rr[1])
		rr[4] = 0;
	if (rr[1] < rr[0])
		rr[4] = 1;
	rr[3] = msh_get_specials(c);
	if (rr[1] == rr[0])
		return (msh_prefix_redirect(cmd, i, c, rr));
	else
		return (msh_postfix_redirect(cmd, i, c, rr));
}
