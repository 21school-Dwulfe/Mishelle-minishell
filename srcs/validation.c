/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:13:01 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:18:22 by dwulfe           ###   ########.fr       */
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
		|| !ft_strncmp(tmp[1] , "((", len[1]) || ft_strncmp(tmp[1], "<<", len[1])
		|| !ft_strncmp(tmp[1], "))", len[1]) || ft_strncmp(tmp[1], ">>", len[1]))
		return (msh_unexpected_token_error(tmp[1], len[1]));
	return (0);
}

int	msh_validation_brackets(char *str, int *i)
{

	(void)str;
	(void)i;
	// char *tmp[2];

	// tmp[0] = msh_get_prev_word(str, *i, ";|<> ");
	// tmp[1] = msh_get_path(tmp, g_info.env);
	// if (!msh_execution_validation(tmp[0]) && (!tmp[1] && !msh_is_build(tmp)))
	// {

	// }
	return (0);

}

int msh_validation_double_amp(char *str, int *i)
{
	char *tmp[2];

	tmp[0] = msh_get_prev_word(str, *i, " ");
	tmp[1] = msh_get_next_word(str, *i, " ");
	if (ft_strcmp(tmp[0], "") == 0)
		return(msh_unexpected_token_error("&&", 2));
	else if (ft_strcmp(tmp[1], "") == 0)
		return (-11);
	return (0);
}

int	msh_validation_double_pipe(char *str, int *i)
{
	char *tmp[2];

	tmp[0] = msh_get_prev_word(str, *i, " ");
	tmp[1] = msh_get_next_word(str, *i, " ");
	if (ft_strcmp(tmp[0], "") == 0)
		return(msh_unexpected_token_error("||", 2));
	else if (ft_strcmp(tmp[1], "") == 0)
		return (-10);
	return (0);
}

int	msh_validation_closest_chars(char *str, int *i)
{
	if (str[*i] && (str[*i] == ')' || str[*i] == '('))
		return (msh_validation_brackets(str, i));
	if (str[*i] == '|')
		return (msh_validation_pipe(str, i));
	if (str[*i] == '>' || str[*i] == '<')
		return (msh_validation_redirs(str, i));
	if (str[*i] == '&' || str[*i] == '&')
		return (msh_validation_double_amp(str, i));
	return (0);
}
