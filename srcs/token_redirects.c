/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:45:50 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/25 16:26:03 by dwulfe           ###   ########.fr       */
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

	(void)len;
	len = ft_strlen(value);
	name = msh_redirects_value_to_name(value);
	msh_push_redirect(&cmd->redirects, name, sp);
	return (0);
}

void	msh_cut_quotes(char **str, int j, int len)
{
	int		i;
	char	*ptr;
	int		full_len;

	i = j;
	ptr = *str;
	while (ptr[i] && i < len - 1)
	{
		if ((ptr[i] == '"' && ptr[i + 1] == '"')
			|| (ptr[i] == '\'' && ptr[i + 1] == '\''))
		{
			full_len = ft_strlen(ptr);
			ft_memset(ptr + i, '\0', 2);
			*str = msh_concat_str(ptr, full_len, NULL);
			ft_strdel(&ptr);
			i -= 2;
			ptr = *str;
		}
		i++;
	}
}

char	*msh_token_redirect(char *str, int *index)
{
	int		i[3];
	char	*result;
	char	c;

	i[0] = *index;
	i[1] = *index;
	i[2] = *index;
	result = NULL;
	c = str[i[0]];
	while (*index - 1 > -1 && str[*index - 1] != ' '
		&& ft_isdigit(str[*index - 1]))
		(*index)--;
	while (str[i[1]] && str[i[1]] == c)
		i[1]++;
	while (str[i[1]] && str[i[1]] == ' ')
		i[1]++;
	while (str[i[1]] && !ft_strchr(" |;<>&", str[i[1]]))
		i[1]++;
	if (i[1] != i[2])
		result = ft_strndup(str + *index, i[1] - *index);
	return (result);
}
