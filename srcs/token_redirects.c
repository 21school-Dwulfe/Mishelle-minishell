/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:45:50 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 23:59:08 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_conditions_redirects(char *str, int *i)
{
	int	in;

	in = (*i) + 1;
	if (str[*i] == '>' && str[in] != '>')
		return (REDIRECT);
	if (str[*i] == '<' && str[in] != '<')
		return (R_REDIRECT);
	if (str[*i] == '>' && str[in] == '>')
		return (D_REDIRECT);
	if (str[*i] == '<' && str[in] == '<')
		return (HEREDOC);
	return (0);
}

char	*msh_redirects_value_to_name(char *value)
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

int	msh_convert_redirects(t_command *cmd, char *value, char *name, int sp)
{
	int		len;

	len = ft_strlen(value);
	name = msh_redirects_value_to_name(value);
	msh_push_redirect(&cmd->redirects, name, sp);
	return (0);
}

char	*msh_token_redirect(char *str, int *index)
{
	int		i[2];
	char	*result;
	int		word;
	char	c;

	i[0] = *index;
	i[1] = *index;
	word = 0;
	result = NULL;
	c = str[i[0]];
	while (i[0] - 1 > -1 && str[i[0] - 1] != ' ' && ft_isdigit(str[i[0] - 1]))
		i[0]--;
	while (str[i[1]] && str[i[1]] == c)
		i[1]++;
	while (str[i[1]] && str[i[1]] == ' ')
		i[1]++;
	word = i[1];
	while (str[i[1]] && !ft_strchr(" |;<>&", str[i[1]]))
		i[1]++;
	if (word && (i[0] != *index || i[1] != *index))
		result = ft_strndup(str + *i, i[1] - *i);
	return (result);
}
