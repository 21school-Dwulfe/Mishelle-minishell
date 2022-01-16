/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:25 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	int	j;
	int	res;

	j = 0;
	while (j < 13)
	{
		res = g_info.condition[j](str, i);
		if (res != 0)
			return (*specials = res);
		j++;
	}
	return (*specials = 0);
}

void	msh_save_command(char *str, int start, int end, int specials)
{
	t_command	*cmd;
	char		*tmp;

	cmd = g_info.cur_cmd;
	tmp = ft_strndup(str + start, end - start);
	cmd->prev->args = ft_split(tmp, ' ');
	cmd->prev->num_args = ft_str_count(cmd->prev->args);
	cmd->prev->specials = specials;
	if (specials == PIPE || specials == DOUBLE_PIPE || specials == DOUBLE_AMP)
	{
		cmd->prev->piped = (specials == PIPE);
		msh_add_command(&cmd, NULL);
	}
	g_info.num_of_commands++;
	ft_strdel(&tmp);
}

void	msh_input_call(char **str, int *i)
{
	char	*line;
	char	*tmp;

	(void)i;
	msh_readline(">", &line);
	tmp = *str;
	*str = ft_strjoin(tmp, line);
	ft_strdel(&line);
	ft_strdel(&tmp);
	*i = 0;
}

int	msh_parse(char **str)
{
	int			i[3];

	ft_bzero(i, sizeof(int) * 3);
	while (str[0][i[1]])
	{
		if (i[2] == 1 || i[2] == 2 || i[2] == 11 || i[2] == 10)
			i[0] = i[1];
		if (msh_check_special_signs(*str, &i[1], &i[2]) == ERROR)
			return (-1);
		if (i[2] < -1)
			msh_input_call(str, &i[1]);
		if (i[2] == -1 || i[2] > 9 )
			msh_side_effect(str, &i[1], &i[2]);
		if ((i[2] != 0 && i[2] < 3) || i[2] == 11 || i[2] == 10)
			msh_save_command(*str, i[0], i[1], i[2]);
		if (i[2] >= 12 && i[2] < 20)
			i[2] = 0;
		if (i[2] == -1)
			break ;
		i[1]++;
	}
	return(0);
}
