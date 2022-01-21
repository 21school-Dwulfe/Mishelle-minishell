/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_strings_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:46:46 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 20:37:07 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_replace_null_arg(t_command *cmd)
{
	char	**tmp;

	tmp = msh_concat_args(cmd->args, cmd->num_args);
	free(cmd->args);
	cmd->args = tmp;
	cmd->num_args = ft_str_count(cmd->args);
}

void	msh_specials_cut(char **str, int *i, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *i, '\0', sizeof(char) * end);
	if (len > end)
	{
		tmp = *str;
		*str = msh_concat_str(*str, len, NULL);
		ft_strdel(&tmp);
		if (*i - 1 >= 0)
			(*i)--;
	}
}

void	msh_specials_replace(char **str, char *insertion, int *start, int len)
{
	char	*tmp;
	int		l;

	tmp = *str;
	l = ft_strlen(*str);
	ft_memset(tmp + *start, '\0', sizeof(char) * len);
	if (l > len || ft_strlen(insertion))
	{
		*str = msh_concat_str(*str, l, insertion);
		ft_strdel(&tmp);
		if (*start - 1 >= 0)
			(*start)--;
	}
}

//; | < > space
char	*msh_get_prev_word(char *str, int length, char *set)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	if (length - 1 < 0)
		return (NULL);
	i = length - 1;
	while (i - 1 > -1 && str[i] == ' ')
	{
		spaces++;
		i--;
	}
	while (i - 1 > -1 && !ft_strchr(set, str[i - 1]))
		i--;
	return (ft_strndup(str + i, length - i - spaces));
}

char	*msh_get_next_word(char *str, int length, char *set)
{
	int	i;
	int	spaces;

	spaces = 0;
	i = length + 1;
	while (str[i] && str[i] == ' ')
	{
		spaces++;
		i++;
	}
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	return (ft_strndup(str + length + 1 + spaces, i - length - spaces));
}
