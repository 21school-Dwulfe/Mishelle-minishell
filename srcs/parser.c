/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:25 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 16:09:11 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_multiple_iterator(int num, int *i, int sign)
{
	int	in;

	in = 0;
	while (in < num)
	{
		if (sign > -1)
			(*i)++;
		else
			(*i)--;
		in++;
	}
	return (in);
}

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	int	j;
	int	res;

	j = 0;
	while (j < 9)
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

	cmd = msh_last_cmd();
	tmp = ft_strndup(str + start, end - start);
	if (cmd->args)
		msh_add_command(&cmd, ft_split(tmp, ' '));
	else
		cmd->args = ft_split(tmp, ' ');
	cmd->num_args = ft_str_count(cmd->args);
	cmd->specials = specials;
	if (specials == PIPE)
		cmd->piped++;
	g_info.num_of_commands++;
	ft_strdel(&tmp);
}

//-10 wait for command
//-11 wait for command

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

void	msh_cut_effect(char **str, int *i)
{
	t_command	*command;
	t_arg		*tok;
	char		*prev_word;
	
	command = msh_last_cmd();
	prev_word = msh_get_prev_word(*str, *i, "|;<> ");
	if (msh_is_token(prev_word))
	{
		tok = msh_get_token_value(command, prev_word);
		if (str[0][*i + 2] == ' ')
			tok->is_prefix = 0;
	}
	msh_specials_cut(str, i, 2);
}

int	msh_parse(char *str)
{
	int			i[3];

	ft_bzero(i, sizeof(int) * 3);
	while (str[i[1]])
	{
		if (i[2] == 1 || i[2] == 2)
			i[0] = i[1];
		if (msh_check_special_signs(str, &i[1], &i[2]) == ERROR)
			return (-1);
		if (i[2] < -1)
			msh_input_call(&str, &i[1]);
		if (i[2] == -1 || (i[2] > 12 && i[2] < 20))
			msh_choose_effect(&str, &i[1], i[2]);
		if (i[2] == 22 || i[2] == 23)
			msh_cut_effect(&str, &i[1]);
		if (i[2] != 0 && i[2] < 3)
			msh_save_command(str, i[0], i[1], i[2]);
		if (i[2] >= 12 && i[2] < 20)
			i[2] = 0;
		i[1]++;
	}
	if (g_info.num_token)
		ft_strdel(&str);
	return(0);
}
