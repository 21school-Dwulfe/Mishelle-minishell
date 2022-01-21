/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:13:01 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 16:16:46 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_validation_redirs(char *str, int *i)
{
	int		l[4];
	char	*ptr;

	ptr = NULL;
	ft_bzero(l, sizeof(int) * 4);
	l[0] = *i;
	while (str[l[0]] == str[*i] && (l[0] - *i) + 1 < 3)
			l[0]++;
	while (str[l[0]] == ' ')
		l[0]++;
	if (str[l[0]] == '<' && str[l[0] + 1] == '>')
		return (msh_unexpected_token_error(&str[l[0]], 2));
	ptr = ft_strchr("|;<>", str[l[0]]);
	if (ptr)
		l[2] = *ptr;
	if (str[l[0]] == '\0')
		return (msh_unexpected_token_error("newline", 7));
	if (!(ft_abs(l[2] - str[*i]) == 2))
		l[3] = 1;
	l[1] = l[0];
	while (str[l[1]] == l[2] && l[1] + l[3] - l[0] < 3)
		l[1]++;
	if (l[2] && l[2] != 'n')
		return (msh_unexpected_token_error(str + l[0], l[1] - l[0]));
	return (0);
}

int	msh_validate_line(char *line)
{
	int				i;
	unsigned int	ascii[256];

	i = 0;
	ft_bzero(ascii, sizeof(char) * 256);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			ascii[(unsigned char)line[i]]++;
		i++;
	}
	if (ft_strlen(line) == ascii[32])
		return (1);
	return (0);
}

int	msh_validation_pipe(char *str, int *i)
{
	char	*tmp[2];
	int		len[2];

	(void)str;
	tmp[0] = msh_get_prev_word(str, *i, " ");
	tmp[1] = msh_get_next_word(str, *i, " ");
	len[0] = (int)ft_strlen(tmp[0]);
	len[1] = (int)ft_strlen(tmp[1]);
	if (len[1] > 2)
		len[1] = 2;
	if (*i == 0 || !ft_strncmp(tmp[0], "||", len[0])
		|| !ft_strncmp(tmp[1], "((", len[1])
		|| !ft_strncmp(tmp[1], "<<", len[1])
		|| !ft_strncmp(tmp[1], "))", len[1])
		|| !ft_strncmp(tmp[1], ">>", len[1]))
	{
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
		return (msh_unexpected_token_error(tmp[1], len[1]));
	}
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	return (0);
}

int	msh_validation_closest_chars(char *str, int *i)
{
	if (str[*i] == '|')
		return (msh_validation_pipe(str, i));
	if (str[*i] == '>' || str[*i] == '<')
		return (msh_validation_redirs(str, i));
	if (str[*i] == '&' && str[*i + 1] == '&')
		return (msh_validation_double_amp(str, i));
	return (0);
}

int	msh_export_invalid(char *arg)
{
	int	i[4];
	int	res;
	int	length;

	res = 0;
	i[0] = 0;
	length = ft_strlen(arg);
	if (!arg || (!ft_isalpha(arg[0]) && arg[i[0]] != '_')
		|| ft_ch_count(arg, '+') > 1)
		return ((++res));
	i[1] = ft_index_of(arg, '+', 0);
	if (i[1] > 0)
		i[2] = i[1];
	else if (i[1] == -1)
		i[2] = ft_index_of(arg, '=', 1);
	else
		return ((++res));
	if (length > 2 && arg[i[1]] == '+' && arg[i[1] + 1] != '=')
		return ((++res));
	while (length > 1 && !res && ++i[0] < i[2])
		if (!ft_isalnum(arg[i[0]]) && arg[i[0]] != '_')
			return ((++res));
	return (0);
}
