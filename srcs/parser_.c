/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:25 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 22:30:43 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_check_special_signs(char *str, int *i)
{
	int	j;
	int	res;

	j = 0;
	while (j < 14)
	{
		res = g_info.condition[j](str, i);
		if (res != 0)
			return (res);
		j++;
	}
	return (0);
}

void	msh_save_command(char *str, int start, int end, int specials)
{
	t_command	*cmd;
	char		*tmp;

	cmd = g_info.cur_cmd;
	tmp = ft_strndup(str + start, end - start);
	cmd->prev->args = ft_split(tmp, ' ');
	cmd->prev->n_args = ft_str_count(cmd->prev->args);
	cmd->prev->specials = specials;
	if (specials == PIPE || specials == DOUBLE_PIPE || specials == DOUBLE_AMP)
	{
		cmd->prev->piped = (specials == PIPE);
		msh_add_command(&cmd, NULL);
	}
	g_info.num_of_commands++;
	ft_strdel(&tmp);
}

int	msh_parse(char **str)
{
	int	i[3];

	ft_bzero(i, sizeof(int) * 3);
	while (str[0][i[1]])
	{
		if (i[2] == 1 || i[2] == 2 || i[2] == 11 || i[2] == 10)
			i[0] = i[1];
		i[2] = msh_check_special_signs(*str, &i[1]);
		if (i[2] == ERROR)
			return (-1);
		if (i[2] < -1)
			msh_input_call(str, &i[1]);
		if (i[2] != 0)
			msh_side_effect(str, &i[1], &i[2]);
		if (i[2] == 0 || i[2] < 4)
			i[1]++;
		if (str[0][i[1]] == '\0' || (i[2] != 0 && i[2] < 3)
			|| i[2] == 11 || i[2] == 10)
			msh_save_command(*str, i[0], i[1], i[2]);
		if (i[2] == -1)
			break ;
	}
	return (0);
}
